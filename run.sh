#!/bin/bash
g++ -std=c++11 main.cpp
./a.out $1
python3 draw.py $1
rm a.out
$SHELL