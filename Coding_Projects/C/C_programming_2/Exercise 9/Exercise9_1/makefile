
CC=gcc

CFLAGS+=-Wall -g

EXECUTABLE=Exercise9_1

OBJECTS=

all: $(OBJECTS) Exercise9_1.c
	$(CC) $(CFLAGS) $(OBJECTS) Exercise9_1.c -o $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
