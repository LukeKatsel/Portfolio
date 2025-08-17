

CC=gcc

CFLAGS+=-Wall -g

OBJECTS=

all: Exercise11_4a.c Exercise11_4b.c
	$(CC) $(CFLAGS) Exercise11_4a.c -o Exercise11_4a -lpthread 
	$(CC) $(CFLAGS) Exercise11_4b.c -o Exercise11_4b -lpthread 


clean:
	rm -f *~
	rm -f *.o
	rm -f Exercise11_4a
	rm -f Exercise11_4b

run:
	./Exercise11_4a&
	./Exercise11_4b&

kill:
	killall -q Exercise11_4a
	killall -q Exercise11_4b
