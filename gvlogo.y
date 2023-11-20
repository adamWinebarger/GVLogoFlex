%{
#define WIDTH 640
#define HEIGHT 480
#define COLOR_MAX 20
#define VARMAX 100

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

enum dataType {
	ColorType,
	Numeric,
	StringType
};

static SDL_Window* window;
static SDL_Renderer* rend;
static SDL_Texture* texture;
static SDL_Thread* background_id;
static SDL_Event event;
static int running = 1;
static const int PEN_EVENT = SDL_USEREVENT + 1;
static const int DRAW_EVENT = SDL_USEREVENT + 2;
static const int COLOR_EVENT = SDL_USEREVENT + 3;

//May as well do all of our data types here

typedef struct color_t {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color;

typedef struct {
	color col;
	char name[32];
} namedColor;

typedef struct {
	char name[32];
	char contents[512];
} string;

typedef struct {
	char name[32];
	float contents;
} num;

static namedColor colorTable[COLOR_MAX]; //might want to load some initial colors into here but we'll come back to This
static int colorCount = 0;

static string stringVars[VARMAX];
static int stringCount = 0;

static num numVars[VARMAX];
static int numCount = 0;

static color current_color;
static double x = WIDTH / 2;
static double y = HEIGHT / 2;
static int pen_state = 1;	//1 = down, 0 = up... basically a boolean
static double direction = 0.0; //angle in degrees. positive changes are clockwise, negatives are counter
//I wonder if it has a catch to modulo 360.0

int yylex(void);
int yyerror(const char* s);
void startup();
int run(void* data);
void prompt();
void penup();
void pendown();
void go2(double newX, double newY); //our two functions we gotta add in
void where();
void move(int num);
void turn(int dir);
void output(const char* s);
void change_color(int r, int g, int b);
void clear();
void save(const char* path);
void shutdown();

//functions for the variable handling
void addColor(const char* name, int r, int g, int b);
void getColorValues(const char* name);
void setColorValues(const char* name, int r, int g, int b); //we'll use a char to determine which of these we want to set

int check4Color(const char* name);

void addString(const char* name, const char* str);
char* getStringValue(const char* name);
void setStringValue(const char* name, const char* newVal);

int check4String(const char* name);

void addNum(char* name, float value);
float getNumVal(const char* name); //might change this one to a float but I kind of want to keep consistency here for Now
void setNumValue(const char* name, float newVal);
int check4Num(char* name);
void numNotFound(char* name) {printf("Error! Numeric variable not found: %s\n", name);}
void stringNotFound(char * name) {printf("Error! String var not found: %s\n", name);}
void colorNotFound(char *name) {printf("Error! Color not found: %s\n", name);}

void printVariableContents(char* name);
void expressionOutput(float f);

%}

%union {
	float f;
	char* s;
}

%locations

%token SEP
%token PENUP
%token PENDOWN
%token PRINT
%token CHANGE_COLOR
%token COLOR
%token CLEAR
%token TURN
%token LOOP
%token MOVE
%token NUMBER
%token END
%token SAVE
%token WHERE
%token GOTO
%token EXIT
%token PLUS SUB MULT DIV EQUALS QUOTE OPENPAREN CLOSEDPAREN COMMA
%token NUM STRINGVAR
%token<s> STRING QSTRING VAR
%type<f> expression expression_list NUMBER


%%

program:		statement_list END				{ printf("Program complete."); shutdown(); exit(0); }

		;
statement_list:		statement
		|	statement statement_list
		;
statement:		command SEP					{ prompt(); }
		|	error '\n'					{ yyerrok; prompt(); }
		;
command:		PENUP						{ printf("Pen is up\n"); penup(); }
		| 			PENDOWN					{printf("Pen is down\n"); pendown();}
		|				PRINT QUOTE STRING QUOTE													{output($3); /*This might be wrong; may need to have it take a variable number of arguments. See cdir*/}
		|				PRINT VAR {printVariableContents($2);	}
		|				PRINT expression_list {printf("%f\n", $2);}
		|				VAR {printVariableContents($1);}
		|				expression_list {printf("%f\n", $1);}
		|				STRING {output($1);}
		|				CHANGE_COLOR NUMBER NUMBER NUMBER		{change_color((int) $2, (int) $3, (int) $4);}
		|				CHANGE_COLOR VAR {
			if (check4Color($2) != -1) {
				int i = check4Color($2);
				change_color(colorTable[i].col.r, colorTable[i].col.g, colorTable[i].col.b);
			} else {colorNotFound($2);}
		}
		|				COLOR VAR EQUALS NUMBER NUMBER NUMBER					{((check4Color($2)) == -1) ? addColor($2, (int) $4, (int) $5, (int) $6) : colorNotFound($2); /*Are these just the same thing?*/}
		|				VAR EQUALS NUMBER NUMBER NUMBER {(check4Color($1)) >= 0 ? setColorValues($1, (int) $3, (int) $4, (int) $5) : colorNotFound($1);}
		|				CLEAR						{clear();}
		|				TURN expression 						{turn((int) $2);}
		|				TURN VAR {(check4Num($2) != -1) ? turn((int) getNumVal($2)) : numNotFound($2);}
		|				LOOP						{printf("Loop functionality coming soon!\n");}
		|				MOVE expression 		{move((int) $2);}
		| 			MOVE VAR {(check4Num($2) != -1) ? move((int) getNumVal($2)) : numNotFound($2);}
		|				END 						{shutdown();}
		|				SAVE VAR 						{save($2); /*May need to make use of STRING here*/}
		|				WHERE 				{where();}
		|				GOTO expression expression {go2((int) $2, (int) $3);}
		|				EXIT 				{shutdown();}
		|				SEP 						{ ; }
		|				STRINGVAR VAR EQUALS STRING {((check4String($2)) == -1) ? addString($2, $4) : exit(1);}
		| 			VAR EQUALS STRING {check4String($1) > -1 ? setStringValue($1, $3) : yyerrok;}
		|				NUM VAR EQUALS expression_list {check4Num($2) == -1 ? addNum($2, $4) : yyerrok;}
		|				VAR EQUALS expression_list {check4Num($1) > -1? setNumValue($1, $3) : yyerrok;}
		;
expression_list:	expression
		| 	expression expression_list

		;
expression:		NUMBER PLUS expression				{ $$ = $1 + $3; }
		|	NUMBER MULT expression				{ $$ = $1 * $3; }
		|	NUMBER SUB expression				{ $$ = $1 - $3; }
		|	NUMBER DIV expression				{ $$ = $1 / $3; }
		|	NUMBER {$$ = $1;}
		| VAR PLUS expression {check4Num($1) != -1 ? $$ = getNumVal($1) + $3 : numNotFound($1);}
		| VAR MULT expression {check4Num($1) != -1 ? $$ = getNumVal($1)* $3 : numNotFound($1);}
		| VAR SUB expression {check4Num($1) != -1 ? $$ = getNumVal($1) - $3 : numNotFound($1);}
		| VAR DIV expression {check4Num($1) != -1 ? $$ = getNumVal($1) / $3 : numNotFound($1);}
		| VAR {check4Num($1) != -1 ? $$ = getNumVal($1) : numNotFound($1);}
		;

%%

int main(int argc, char** argv){
	startup();
	return 0;
}

int yyerror(const char* s){

	printf("Error: %s\n", s);
	if (strcmp(s, "syntax error") == 0)
		exit(1);
	if (strcmp(s, "Lexing Syntax error.") == 0)
		printf("Input ;; to continue...\n");
	return -1;

	/* printf("Error: %s\n", s);

    // Advance the input until a newline or a token that can continue parsing
    while (1) {
        int token = yylex();
        if (token == '\n' || token == 0 ) {
            return -1;  // Continue parsing after newline or end of file
        }
    } */
};

void prompt(){
	printf("gv_logo > ");
}

void penup(){
	event.type = PEN_EVENT;
	event.user.code = 0;
	SDL_PushEvent(&event);
}

void pendown() {
	event.type = PEN_EVENT;
	event.user.code = 1;
	SDL_PushEvent(&event);
}

//Let's put goto and where here
void go2(double newX, double newY) {
		if(!pen_state) {
			x =  newX;
			y =  newY; //might have to do more work here
		} else {
			event.type = DRAW_EVENT;
			event.user.code = 5;
			event.user.data1 = (int) newX;
			event.user.data2 = (int) newY;
			SDL_PushEvent(&event);
		}
}

void where() {
		printf("Current location: x = %lf; y = %lf\n", x, y);
}

void move(int num){
	printf("Moving %d in direction %lf\n", num, direction);
	event.type = DRAW_EVENT;
	event.user.code = 1;
	event.user.data1 = num;
	SDL_PushEvent(&event);
}

void turn(int dir){
	event.type = PEN_EVENT;
	event.user.code = 2;
	event.user.data1 = dir;
	printf("Turn has turned by %d.\n", dir);
	SDL_PushEvent(&event);
}

void output(const char* s){
	printf("%s\n", s);
	//free(s);
}

void change_color(int r, int g, int b){
	event.type = COLOR_EVENT;
	current_color.r = r;
	current_color.g = g;
	current_color.b = b;
	SDL_PushEvent(&event);
}

void clear(){
	event.type = DRAW_EVENT;
	event.user.code = 2;
	SDL_PushEvent(&event);
}

void startup(){
	current_color.r = 0;
	current_color.g = 255;
	current_color.b = 0;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("GV-Logo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		yyerror("Can't create SDL window.\n");
	}

	//rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	if(texture == NULL){
		printf("Texture NULL.\n");
		exit(1);
	}
	SDL_SetRenderTarget(rend, texture);
	SDL_RenderSetScale(rend, 3.0, 3.0);

	SDL_SetRenderTarget(rend, NULL);
	SDL_SetRenderDrawColor(rend, 0, 255, 0, 127);

	background_id = SDL_CreateThread(run, "Parser thread", (void*)NULL);
	if(background_id == NULL){
		yyerror("Can't create thread.");
	}
	while(running){
		SDL_Event e;
		while( SDL_PollEvent(&e) ){
			if(e.type == SDL_QUIT){
				running = 0;
			}
			if(e.type == PEN_EVENT){
				if(e.user.code == 2){
					//so this is just reorienting the pen
					//which is also done for some reason when we clear
					double degrees = ((int)e.user.data1) * M_PI / 180.0;
					direction += degrees;
				}
				pen_state = e.user.code;
			}
			if(e.type == DRAW_EVENT){
				if(e.user.code == 1){
					//This is where we're actually moving the pen
					int num = (int)event.user.data1;
					double x2 = x + num * cos(direction);
					double y2 = y + num * sin(direction);
					if(pen_state != 0){
						SDL_SetRenderTarget(rend, texture);
						SDL_RenderDrawLine(rend, x, y, x2, y2);
						SDL_SetRenderTarget(rend, NULL);
						SDL_RenderCopy(rend, texture, NULL, NULL);
					}
					x = x2;
					y = y2;
				} else if(e.user.code == 2){
					SDL_SetRenderTarget(rend, texture);
					SDL_RenderClear(rend);
					SDL_SetTextureColorMod(texture, current_color.r, current_color.g, current_color.b);
					SDL_SetRenderTarget(rend, NULL);
					SDL_RenderClear(rend);
				} else if(e.user.code == 5) {
					//I guess we could just use this regardless... we'll come back to that
					int x2 = (int) event.user.data1,
					y2 = (int) event.user.data2;

					if (pen_state != 0) {
						SDL_SetRenderTarget(rend, texture);
						SDL_RenderDrawLine(rend, x, y, (double) x2, (double) y2);
						SDL_SetRenderTarget(rend, NULL);
						SDL_RenderCopy(rend, texture, NULL, NULL);
						x = (double) x2;
						y = (double) y2;
					}
				}
			}
			if(e.type == COLOR_EVENT){
				SDL_SetRenderTarget(rend, NULL);
				SDL_SetRenderDrawColor(rend, current_color.r, current_color.g, current_color.b, 255);
			}
			if(e.type == SDL_KEYDOWN){
			}

		}
		//SDL_RenderClear(rend);
		SDL_RenderPresent(rend);
		SDL_Delay(1000 / 60);
	}
}

int run(void* data){
	prompt();
	return yyparse();
}

void shutdown(){
	running = 0;
	SDL_WaitThread(background_id, NULL);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void save(const char* path){
	SDL_Surface *surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(rend, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
	SDL_SaveBMP(surface, path);
	SDL_FreeSurface(surface);
}

//And I guess we'll just throw our functions for variables down here.
void addColor(const char* name, int r, int g, int b) {
	if (colorCount >= COLOR_MAX) {
		printf("You've made too many colors, JAck\n");
		return;
	}

	if (strlen(name) > 32) {
		printf("That name is too long");
		return;
	}

	strcpy(colorTable[colorCount].name, name);
	colorTable[colorCount].col.r = r;
	colorTable[colorCount].col.g = g;
	colorTable[colorCount].col.b = b;
	colorCount++;
}

void getColorValues(const char* name) {
	for (int i = 0; i < colorCount; i++) {
		if (strcmp(colorTable[i].name, name) == 0) {
			printf("Color %s: r: %d, g: %d, b: %d\n", colorTable[i].name, colorTable[i].col.r,
				colorTable[i].col.g, colorTable[i].col.b);
			return;
		}
	}
	printf("Unable to find color: %s", name);
}

int check4Color(const char* name) {
	for (int i = 0; i < colorCount; i++)
		if (strcmp(colorTable[i].name, name) == 0)
			return i;

	return -1;
}

void setColorValues(const char* name, int r, int g, int b) {
	for (int i = 0; i < colorCount; i++) {
		if (strcmp(colorTable[i].name, name) == 0) {

			colorTable[i].col.r = r;
			colorTable[i].col.g = b;
			colorTable[i].col.b = g;

			printf("Color %s values changed to (%d,%d,%d)\n", name, colorTable[i].col.r, colorTable[i].col.g, colorTable[i].col.b);
			return;
		}
	}

	printf("Color %s not found.\n", name);
}

void addString(const char* name, const char* str) {
	if (stringCount >= VARMAX) {
		printf("You have declared too many strings");
		return;
	}

	if (strlen(name) > 32) {
		printf("Name declaration too long\n");
		return;
	}

	//printf("String %s stored as %s", name, str);
	strcpy(stringVars[stringCount].name, name);
	strcpy(stringVars[stringCount++].contents, str);
}

char* getStringValue(const char* name) {
	for (int i = 0; i < stringCount; i++)
		if (strcmp(stringVars[i].name, name) == 0) {
			//printf("%s\n", stringVars[i].contents);
			return stringVars[i].contents;
		}
		printf("No variable found: %s", name);
		return NULL;
}

void setStringValue(const char* name, const char* newVal) {
	for (int i = 0; i < stringCount; i++) {
		if (strcmp(stringVars[i].name, name)) {
			strncpy(stringVars[i].contents, newVal, strlen(newVal));
			return;
		}
	}

	printf("No variable found: %s\n", name);
}

int check4String(const char* name) {
	for (int i = 0; i < stringCount; i++) {
		if (strcmp(stringVars[i].name, name) == 0)
			return i;
	}

	//printf("Unable to find String variable: %s\n", name);
	return -1;
}

void addNum(char* name, float value) {
	if (numCount >= VARMAX) {
		printf("You have made too many numeric variables\n");
		return;
	}

	if (strlen(name) > 32) {
		printf("This name is too long\n");
		return;
	}

	//printf("variable %s set to %d\n", name, value);
	strcpy(numVars[numCount].name, name);
	numVars[numCount].contents = value;
	numCount++;
}

float getNumVal(const char* name) {
	for (int i = 0; i < numCount; i++)
		if (strcmp(numVars[i].name, name) == 0)
			return numVars[i].contents;

	printf("Unable to find numeric variable: %s\n", name);
	return 0.0; //this should theoretically be unreachable if we design this shit right
}
void setNumValue(const char* name, float newVal) {
	for (int i = 0; i < numCount; i++)
		if (strcmp(numVars[i].name, name) == 0) {
			numVars[i].contents = newVal;
			return;
		}

	printf("Unable to find numeric value\n");
}

int check4Num(char* name) {
	for (int i = 0; i < numCount; i++)
		if (strcmp(numVars[i].name, name) == 0)
			return i;

	return -1;
}

void printVariableContents(char* name) {
	int index;
	if ((index = check4Color(name)) != -1) {
		printf("Color %s: r: %d, g: %d, b: %d\n", colorTable[index].name,
			colorTable[index].col.r, colorTable[index].col.g, colorTable[index].col.b);
		return;
	} else if ((index = check4String(name)) != -1) {
		printf("%s\n", stringVars[index].contents);
		return;
	} else if ((index = check4Num(name)) != -1) {
		//printf("%s, %d\n", name, index);
		printf("%f\n", numVars[index].contents);
		return;
	}

	printf("Unable to find variable: %s\n", name);
}

void expressionOutput(float f) {
	printf("%f\n", f);
}
