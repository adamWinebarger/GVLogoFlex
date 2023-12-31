/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gvlogo.y"

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


#line 181 "gvlogo.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "gvlogo.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEP = 3,                        /* SEP  */
  YYSYMBOL_PENUP = 4,                      /* PENUP  */
  YYSYMBOL_PENDOWN = 5,                    /* PENDOWN  */
  YYSYMBOL_PRINT = 6,                      /* PRINT  */
  YYSYMBOL_CHANGE_COLOR = 7,               /* CHANGE_COLOR  */
  YYSYMBOL_COLOR = 8,                      /* COLOR  */
  YYSYMBOL_CLEAR = 9,                      /* CLEAR  */
  YYSYMBOL_TURN = 10,                      /* TURN  */
  YYSYMBOL_LOOP = 11,                      /* LOOP  */
  YYSYMBOL_MOVE = 12,                      /* MOVE  */
  YYSYMBOL_NUMBER = 13,                    /* NUMBER  */
  YYSYMBOL_END = 14,                       /* END  */
  YYSYMBOL_SAVE = 15,                      /* SAVE  */
  YYSYMBOL_WHERE = 16,                     /* WHERE  */
  YYSYMBOL_GOTO = 17,                      /* GOTO  */
  YYSYMBOL_EXIT = 18,                      /* EXIT  */
  YYSYMBOL_PLUS = 19,                      /* PLUS  */
  YYSYMBOL_SUB = 20,                       /* SUB  */
  YYSYMBOL_MULT = 21,                      /* MULT  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_EQUALS = 23,                    /* EQUALS  */
  YYSYMBOL_QUOTE = 24,                     /* QUOTE  */
  YYSYMBOL_OPENPAREN = 25,                 /* OPENPAREN  */
  YYSYMBOL_CLOSEDPAREN = 26,               /* CLOSEDPAREN  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_NUM = 28,                       /* NUM  */
  YYSYMBOL_STRINGVAR = 29,                 /* STRINGVAR  */
  YYSYMBOL_STRING = 30,                    /* STRING  */
  YYSYMBOL_QSTRING = 31,                   /* QSTRING  */
  YYSYMBOL_VAR = 32,                       /* VAR  */
  YYSYMBOL_33_n_ = 33,                     /* '\n'  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_statement_list = 36,            /* statement_list  */
  YYSYMBOL_statement = 37,                 /* statement  */
  YYSYMBOL_command = 38,                   /* command  */
  YYSYMBOL_expression_list = 39,           /* expression_list  */
  YYSYMBOL_expression = 40                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  84

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   142,   142,   145,   146,   148,   149,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   185,   186,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEP", "PENUP",
  "PENDOWN", "PRINT", "CHANGE_COLOR", "COLOR", "CLEAR", "TURN", "LOOP",
  "MOVE", "NUMBER", "END", "SAVE", "WHERE", "GOTO", "EXIT", "PLUS", "SUB",
  "MULT", "DIV", "EQUALS", "QUOTE", "OPENPAREN", "CLOSEDPAREN", "COMMA",
  "NUM", "STRINGVAR", "STRING", "QSTRING", "VAR", "'\\n'", "$accept",
  "program", "statement_list", "statement", "command", "expression_list",
  "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-13)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      59,   -29,   -30,   -30,   -30,    22,    -3,   -27,   -30,    23,
     -30,    25,    29,   -30,   -23,   -30,    26,   -30,   -16,   -15,
     -30,     4,    44,    31,    59,    49,   -30,    26,   -30,    48,
      -1,   -30,    40,   -30,    33,    60,   -30,    60,   -30,    26,
      26,    26,    26,   -30,    60,    26,    36,    61,    26,    26,
      26,    26,    -2,   -30,   -30,   -30,   -30,   -30,    62,    70,
      72,   -30,   -30,   -30,   -30,   -30,    26,    63,   -30,   -30,
     -30,   -30,    -7,   -30,   -30,   -30,   -30,    77,   -30,   -30,
      79,    81,   -30,   -30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    30,     7,     8,     0,     0,     0,    19,     0,
      22,     0,    41,    25,     0,    27,     0,    29,     0,     0,
      14,    46,     0,     0,     0,     0,    13,    35,     6,     0,
      46,    11,     0,    16,     0,    21,    20,    24,    23,     0,
       0,     0,     0,    26,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     4,     5,    36,     0,     0,
       0,    37,    39,    38,    40,    28,     0,     0,    42,    44,
      43,    45,    41,    32,    34,     9,    15,     0,    33,    31,
       0,     0,    18,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,    71,   -30,   -30,    -5,    -8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    22,    23,    24,    25,    26,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    36,   -10,    38,    28,    34,    80,   -12,    45,    43,
      32,    72,    39,    40,    41,    42,    46,    47,    48,    49,
      50,    51,    57,    48,    49,    50,    51,    52,    73,    33,
      44,    61,    62,    63,    64,    12,    12,    65,    12,    12,
      68,    69,    70,    71,    53,    54,    29,    74,    39,    40,
      41,    42,    56,    59,    30,    35,    60,    37,    44,    66,
       1,    78,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    58,    48,
      49,    50,    51,    76,    67,    77,    75,    18,    19,    20,
      81,    21,    82,    79,    83,    55
};

static const yytype_int8 yycheck[] =
{
       5,     9,     3,    11,    33,    32,    13,     3,    16,    32,
      13,    13,    19,    20,    21,    22,    32,    32,    19,    20,
      21,    22,    27,    19,    20,    21,    22,    23,    30,    32,
      32,    39,    40,    41,    42,    13,    13,    45,    13,    13,
      48,    49,    50,    51,     0,    14,    24,    52,    19,    20,
      21,    22,     3,    13,    32,    32,    23,    32,    32,    23,
       1,    66,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    30,    19,
      20,    21,    22,    13,    23,    13,    24,    28,    29,    30,
      13,    32,    13,    30,    13,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    28,    29,
      30,    32,    35,    36,    37,    38,    39,    40,    33,    24,
      32,    39,    13,    32,    32,    32,    40,    32,    40,    19,
      20,    21,    22,    32,    32,    40,    32,    32,    19,    20,
      21,    22,    23,     0,    14,    36,     3,    39,    30,    13,
      23,    40,    40,    40,    40,    40,    23,    23,    40,    40,
      40,    40,    13,    30,    39,    24,    13,    13,    39,    30,
      13,    13,    13,    13
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    39,    39,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     2,     1,     1,     4,
       2,     2,     1,     1,     1,     4,     2,     6,     5,     1,
       2,     2,     1,     2,     2,     1,     2,     1,     3,     1,
       1,     4,     3,     4,     3,     1,     2,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement_list END  */
#line 142 "gvlogo.y"
                                                                        { printf("Program complete."); shutdown(); exit(0); }
#line 1372 "gvlogo.tab.c"
    break;

  case 5: /* statement: command SEP  */
#line 148 "gvlogo.y"
                                                                        { prompt(); }
#line 1378 "gvlogo.tab.c"
    break;

  case 6: /* statement: error '\n'  */
#line 149 "gvlogo.y"
                                                                        { yyerrok; prompt(); }
#line 1384 "gvlogo.tab.c"
    break;

  case 7: /* command: PENUP  */
#line 151 "gvlogo.y"
                                                                        { printf("Pen is up\n"); penup(); }
#line 1390 "gvlogo.tab.c"
    break;

  case 8: /* command: PENDOWN  */
#line 152 "gvlogo.y"
                                                                                {printf("Pen is down\n"); pendown();}
#line 1396 "gvlogo.tab.c"
    break;

  case 9: /* command: PRINT QUOTE STRING QUOTE  */
#line 153 "gvlogo.y"
                                                                                                                                                                                {output((yyvsp[-1].s)); /*This might be wrong; may need to have it take a variable number of arguments. See cdir*/}
#line 1402 "gvlogo.tab.c"
    break;

  case 10: /* command: PRINT VAR  */
#line 154 "gvlogo.y"
                                                          {printVariableContents((yyvsp[0].s));	}
#line 1408 "gvlogo.tab.c"
    break;

  case 11: /* command: PRINT expression_list  */
#line 155 "gvlogo.y"
                                                                      {printf("%f\n", (yyvsp[0].f));}
#line 1414 "gvlogo.tab.c"
    break;

  case 12: /* command: VAR  */
#line 156 "gvlogo.y"
                                                    {printVariableContents((yyvsp[0].s));}
#line 1420 "gvlogo.tab.c"
    break;

  case 13: /* command: expression_list  */
#line 157 "gvlogo.y"
                                                                {printf("%f\n", (yyvsp[0].f));}
#line 1426 "gvlogo.tab.c"
    break;

  case 14: /* command: STRING  */
#line 158 "gvlogo.y"
                                                       {output((yyvsp[0].s));}
#line 1432 "gvlogo.tab.c"
    break;

  case 15: /* command: CHANGE_COLOR NUMBER NUMBER NUMBER  */
#line 159 "gvlogo.y"
                                                                                                {change_color((int) (yyvsp[-2].f), (int) (yyvsp[-1].f), (int) (yyvsp[0].f));}
#line 1438 "gvlogo.tab.c"
    break;

  case 16: /* command: CHANGE_COLOR VAR  */
#line 160 "gvlogo.y"
                                                                 {
			if (check4Color((yyvsp[0].s)) != -1) {
				int i = check4Color((yyvsp[0].s));
				change_color(colorTable[i].col.r, colorTable[i].col.g, colorTable[i].col.b);
			} else {colorNotFound((yyvsp[0].s));}
		}
#line 1449 "gvlogo.tab.c"
    break;

  case 17: /* command: COLOR VAR EQUALS NUMBER NUMBER NUMBER  */
#line 166 "gvlogo.y"
                                                                                                                        {((check4Color((yyvsp[-4].s))) == -1) ? addColor((yyvsp[-4].s), (int) (yyvsp[-2].f), (int) (yyvsp[-1].f), (int) (yyvsp[0].f)) : colorNotFound((yyvsp[-4].s)); /*Are these just the same thing?*/}
#line 1455 "gvlogo.tab.c"
    break;

  case 18: /* command: VAR EQUALS NUMBER NUMBER NUMBER  */
#line 167 "gvlogo.y"
                                                                                {(check4Color((yyvsp[-4].s))) >= 0 ? setColorValues((yyvsp[-4].s), (int) (yyvsp[-2].f), (int) (yyvsp[-1].f), (int) (yyvsp[0].f)) : colorNotFound((yyvsp[-4].s));}
#line 1461 "gvlogo.tab.c"
    break;

  case 19: /* command: CLEAR  */
#line 168 "gvlogo.y"
                                                                                                {clear();}
#line 1467 "gvlogo.tab.c"
    break;

  case 20: /* command: TURN expression  */
#line 169 "gvlogo.y"
                                                                                                                {turn((int) (yyvsp[0].f));}
#line 1473 "gvlogo.tab.c"
    break;

  case 21: /* command: TURN VAR  */
#line 170 "gvlogo.y"
                                                         {(check4Num((yyvsp[0].s)) != -1) ? turn((int) getNumVal((yyvsp[0].s))) : numNotFound((yyvsp[0].s));}
#line 1479 "gvlogo.tab.c"
    break;

  case 22: /* command: LOOP  */
#line 171 "gvlogo.y"
                                                                                                {printf("Loop functionality coming soon!\n");}
#line 1485 "gvlogo.tab.c"
    break;

  case 23: /* command: MOVE expression  */
#line 172 "gvlogo.y"
                                                                                {move((int) (yyvsp[0].f));}
#line 1491 "gvlogo.tab.c"
    break;

  case 24: /* command: MOVE VAR  */
#line 173 "gvlogo.y"
                                                 {(check4Num((yyvsp[0].s)) != -1) ? move((int) getNumVal((yyvsp[0].s))) : numNotFound((yyvsp[0].s));}
#line 1497 "gvlogo.tab.c"
    break;

  case 25: /* command: END  */
#line 174 "gvlogo.y"
                                                                                                {shutdown();}
#line 1503 "gvlogo.tab.c"
    break;

  case 26: /* command: SAVE VAR  */
#line 175 "gvlogo.y"
                                                                                                        {save((yyvsp[0].s)); /*May need to make use of STRING here*/}
#line 1509 "gvlogo.tab.c"
    break;

  case 27: /* command: WHERE  */
#line 176 "gvlogo.y"
                                                                                {where();}
#line 1515 "gvlogo.tab.c"
    break;

  case 28: /* command: GOTO expression expression  */
#line 177 "gvlogo.y"
                                                                           {go2((int) (yyvsp[-1].f), (int) (yyvsp[0].f));}
#line 1521 "gvlogo.tab.c"
    break;

  case 29: /* command: EXIT  */
#line 178 "gvlogo.y"
                                                                                {shutdown();}
#line 1527 "gvlogo.tab.c"
    break;

  case 30: /* command: SEP  */
#line 179 "gvlogo.y"
                                                                                                { ; }
#line 1533 "gvlogo.tab.c"
    break;

  case 31: /* command: STRINGVAR VAR EQUALS STRING  */
#line 180 "gvlogo.y"
                                                                            {((check4String((yyvsp[-2].s))) == -1) ? addString((yyvsp[-2].s), (yyvsp[0].s)) : exit(1);}
#line 1539 "gvlogo.tab.c"
    break;

  case 32: /* command: VAR EQUALS STRING  */
#line 181 "gvlogo.y"
                                                          {check4String((yyvsp[-2].s)) > -1 ? setStringValue((yyvsp[-2].s), (yyvsp[0].s)) : yyerrok;}
#line 1545 "gvlogo.tab.c"
    break;

  case 33: /* command: NUM VAR EQUALS expression_list  */
#line 182 "gvlogo.y"
                                                                               {check4Num((yyvsp[-2].s)) == -1 ? addNum((yyvsp[-2].s), (yyvsp[0].f)) : yyerrok;}
#line 1551 "gvlogo.tab.c"
    break;

  case 34: /* command: VAR EQUALS expression_list  */
#line 183 "gvlogo.y"
                                                                           {check4Num((yyvsp[-2].s)) > -1? setNumValue((yyvsp[-2].s), (yyvsp[0].f)) : yyerrok;}
#line 1557 "gvlogo.tab.c"
    break;

  case 37: /* expression: NUMBER PLUS expression  */
#line 189 "gvlogo.y"
                                                                        { (yyval.f) = (yyvsp[-2].f) + (yyvsp[0].f); }
#line 1563 "gvlogo.tab.c"
    break;

  case 38: /* expression: NUMBER MULT expression  */
#line 190 "gvlogo.y"
                                                                        { (yyval.f) = (yyvsp[-2].f) * (yyvsp[0].f); }
#line 1569 "gvlogo.tab.c"
    break;

  case 39: /* expression: NUMBER SUB expression  */
#line 191 "gvlogo.y"
                                                                        { (yyval.f) = (yyvsp[-2].f) - (yyvsp[0].f); }
#line 1575 "gvlogo.tab.c"
    break;

  case 40: /* expression: NUMBER DIV expression  */
#line 192 "gvlogo.y"
                                                                        { (yyval.f) = (yyvsp[-2].f) / (yyvsp[0].f); }
#line 1581 "gvlogo.tab.c"
    break;

  case 41: /* expression: NUMBER  */
#line 193 "gvlogo.y"
                               {(yyval.f) = (yyvsp[0].f);}
#line 1587 "gvlogo.tab.c"
    break;

  case 42: /* expression: VAR PLUS expression  */
#line 194 "gvlogo.y"
                                      {check4Num((yyvsp[-2].s)) != -1 ? (yyval.f) = getNumVal((yyvsp[-2].s)) + (yyvsp[0].f) : numNotFound((yyvsp[-2].s));}
#line 1593 "gvlogo.tab.c"
    break;

  case 43: /* expression: VAR MULT expression  */
#line 195 "gvlogo.y"
                                      {check4Num((yyvsp[-2].s)) != -1 ? (yyval.f) = getNumVal((yyvsp[-2].s))* (yyvsp[0].f) : numNotFound((yyvsp[-2].s));}
#line 1599 "gvlogo.tab.c"
    break;

  case 44: /* expression: VAR SUB expression  */
#line 196 "gvlogo.y"
                                     {check4Num((yyvsp[-2].s)) != -1 ? (yyval.f) = getNumVal((yyvsp[-2].s)) - (yyvsp[0].f) : numNotFound((yyvsp[-2].s));}
#line 1605 "gvlogo.tab.c"
    break;

  case 45: /* expression: VAR DIV expression  */
#line 197 "gvlogo.y"
                                     {check4Num((yyvsp[-2].s)) != -1 ? (yyval.f) = getNumVal((yyvsp[-2].s)) / (yyvsp[0].f) : numNotFound((yyvsp[-2].s));}
#line 1611 "gvlogo.tab.c"
    break;

  case 46: /* expression: VAR  */
#line 198 "gvlogo.y"
                      {check4Num((yyvsp[0].s)) != -1 ? (yyval.f) = getNumVal((yyvsp[0].s)) : numNotFound((yyvsp[0].s));}
#line 1617 "gvlogo.tab.c"
    break;


#line 1621 "gvlogo.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 201 "gvlogo.y"


int main(int argc, char** argv){
	startup();
	return 0;
}

int yyerror(const char* s){

	printf("Error: %s\n", s);
	if (strcmp(s, "syntax error") == 0)
		exit(1);
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
