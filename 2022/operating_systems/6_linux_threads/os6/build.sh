#!/bin/sh

echo "Building program..."
g++ -std=c++11 ./main.cpp -o main -Wall -pthread
echo "Finished!"
