#!/bin/sh

echo "Building program..."
g++ -std=c++11 ./main.cpp -o main
g++ -std=c++11 ./program_7.cpp -o program_7
echo "Finished!"
