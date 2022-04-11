cmake -S src -B build
cd build
make
./$(find . -perm +111 -type f -maxdepth 1)
