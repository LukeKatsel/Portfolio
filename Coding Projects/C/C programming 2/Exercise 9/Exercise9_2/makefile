
CC=gcc

CFLAGS+=-Wall -g

EXECUTABLE=Exercise9_2

OBJECTS=

all: $(OBJECTS) Exercise9_2.c
	$(CC) $(CFLAGS) $(OBJECTS) Exercise9_2.c -o $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
