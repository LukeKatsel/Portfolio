

CC=gcc

CFLAGS+=-Wall -g

OBJECTS=

TARGET=Program2

all: $(TARGET)

$(TARGET): $(OBJECTS) Program2.c
	$(CC) $(CFLAGS) $(OBJECTS) Program2.c -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm $(TARGET)

