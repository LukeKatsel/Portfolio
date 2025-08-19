
CC=gcc

CFLAGS+=-Wall -g

EXECUTABLE=Exercise9_3

OBJECTS=circular.o

all: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
