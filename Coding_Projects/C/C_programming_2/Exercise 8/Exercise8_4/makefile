CC=gcc

CFLAGS=-Wall -g

OBJECTS=my_sin.o my_cos.o my_tan.o

all: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o test_8_4 -lm

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f test_9_4


