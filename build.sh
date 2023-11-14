#!/usr/bin/bash

bison -d gvlogo.y
flex gvlogo.l
gcc -o test *.c -lm `sdl2-config --cflags --libs`
