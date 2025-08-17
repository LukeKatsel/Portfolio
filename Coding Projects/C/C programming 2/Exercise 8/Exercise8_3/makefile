CC=gcc

CFLAGS=-Wall -g

OBJECTS= 

all: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o test_8_3 -lm

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f test_9_3


