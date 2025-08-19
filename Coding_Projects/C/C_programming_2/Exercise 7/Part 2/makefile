CC=gcc

CFLAGS+=-std=c11 -Wall -O2 -Warray-bounds

EXECUTABLE=films

OBJECTS=list.o

all: $(OBJECTS) films.c
	$(CC) $(CFLAGS) $(OBJECTS) films.c -o $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
