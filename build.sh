#!/usr/bin/bash

bison -d gvlogo.y
flex gvlogo.l
clang *.c -lfl
