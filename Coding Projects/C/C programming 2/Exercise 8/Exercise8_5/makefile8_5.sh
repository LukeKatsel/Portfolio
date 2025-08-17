#!/bin/bash

if [ "$1" = "clean" ] ; then
    rm -f *~
    rm -f *.o
    rm -f test_9_5
else

gcc -Wall -g -fPIC -c my_sin.c -o my_sin.o
gcc -Wall -g -fPIC -c my_cos.c -o my_cos.o
gcc -Wall -g -fPIC -c my_tan.c -o my_tan.o
ld -r -o test_9_5.o my_sin.o my_cos.o my_tan.o

gcc -shared -o libmy_math.so test_9_5.o

gcc main.c -o test_9_5 -L./ -lmy_math -lm

fi    
