#!/usr/bin/bash

bison -d gvlogo.y
flex gvlogo.l
clang *.c -lfl `sdl2-config --cflags --libs`
