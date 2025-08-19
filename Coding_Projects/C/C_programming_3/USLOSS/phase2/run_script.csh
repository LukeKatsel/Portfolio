#!/bin/csh

/bin/rm outfile.txt
touch outfile.txt

#foreach i ( 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 )
set i = 0
while ($i < 43)
  if ($i < 10) then
    make test0$i
    echo starting test 0$i ....  >> outfile.txt
    echo >> outfile.txt
    ./test0$i >>& outfile.txt
    echo >> outfile.txt
    rm test0$i.o test0$i
  else
    make test$i
    echo starting test $i ....  >> outfile.txt
    echo >> outfile.txt
    ./test$i >>& outfile.txt
    echo >> outfile.txt
    rm test$i.o test$i
  endif
  @ i++
end
