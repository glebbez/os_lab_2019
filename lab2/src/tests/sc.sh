gcc -c ./revert_string.c
ar rcs librevert_string.a revert_string.o
cd ../tests
gcc -c ./tests.c -I../revert_string
gcc tests.o -o ./prg -L../revert_string/ -lrevert_string
./prg
