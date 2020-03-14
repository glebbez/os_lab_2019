gcc -c revert_string.c -o revert_string.static.o
ar rcs revert_string.a main

gcc -c -fPIC revert_string.c -o revert_string.dynamic.o
gcc -shared revert_string.dynamic.o -o revert_string.dynamic.so
