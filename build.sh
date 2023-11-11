#!/usr/bin/bash

bison -d gvlogo.y
flex gvlogo.l
gcc -o test *.c `sdl2-config --cflags --libs`
