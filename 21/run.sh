#! /bin/bash

CFLAGS="-std=c++2a -O3 -Wall -Wextra -g -I../lib/src/"

g++ $CFLAGS one.cc -o one
g++ $CFLAGS two.cc -o two
echo "Part one: $(./one < $1)"
echo "Part two: $(./two < $1)"
