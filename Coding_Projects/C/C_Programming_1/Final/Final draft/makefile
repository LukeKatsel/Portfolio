CC=gcc
CFLAGS= -Wall 
LDFLAGS= -lm
EXECUTABLE=Main
OBJECTS=Main.o Functions.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

Main.o: Main.c Header.h
	$(CC) $(CFLAGS) -c Main.c

Functions.o: Functions.c Header.h
	$(CC) $(CFLAGS) -c Functions.c

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
