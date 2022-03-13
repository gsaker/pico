A simple text editor inspire by GNU nano
Very early stages of development with many bugs 

Known Bugs/Things to implement:
- Unable to remove newlines
- Text cursor not moving as it should when moving between lines
- Can't make new files
- Many other things...

To Compile:
gcc -I inc src/main.c -lcurses -o bin
To Run:
./bin input.txt