#! /bin/bash

CFLAGS="-O0 -std=c++2a -Wall -Wextra -g -I../lib/src"

clang $CFLAGS one.cc -o one
clang $CFLAGS two.cc -o two
echo "Part one: $(./one < $1)"
echo "Part two: $(./two < $1)"
