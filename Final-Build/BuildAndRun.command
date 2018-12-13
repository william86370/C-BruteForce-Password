#!/bin/sh
here="`dirname \"$0\"`"
echo "Building File"
cd "$here" 
make
echo "Running File"
./Bruteforce
