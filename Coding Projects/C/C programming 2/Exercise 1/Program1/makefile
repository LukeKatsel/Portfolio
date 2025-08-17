

TARGET=Program1

CC=gcc

CFLAGS+=-Wall -g -Wl,-Map=$(TARGET).map

OBJECTS=


all: $(OBJECTS) Program1.c
	$(CC) $(CFLAGS) $(OBJECTS) Program1.c -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f *.o
	rm -f *.map
	rm $(TARGET)

