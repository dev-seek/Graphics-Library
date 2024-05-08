#!/bin/sh

set -xe 

mkdir -p ./build/

g++ -Wall -Wextra -ggdb -o ./build/example example.cpp

g++  -Wall -Wextra -ggdb -o ./build/test test.cpp -lm

clang -Wall -Wextra --target=wasm32 -o wasm.o -c ./wasm.cpp
wasm-ld -m wasm32 --no-entry --export-all --allow-undefined -o wasm.wasm wasm.o 

# ./build/example
# ./build/test


