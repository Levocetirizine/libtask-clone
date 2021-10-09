#!/bin/bash

make libtask.a -j`nproc` --quiet
clang++ test.cpp -o test -O0 -g -Wall -L . -l:libtask.a
./test
