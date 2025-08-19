

CC=gcc

CFLAGS+=-Wall -g

OBJECTS=

all: Exercise11_2a.c Exercise11_2b.c
	$(CC) $(CFLAGS) Exercise11_2a.c -o Exercise11_2a
	$(CC) $(CFLAGS) Exercise11_2b.c -o Exercise11_2b

# gcc -Wall -g Exercise12_1.c -o Exercise12_1
clean:
	rm -f *~
	rm -f *.o
	rm -f Exercise11_2a
	rm -f Exercise11_2b

run:
	./Exercise11_2a&
	./Exercise11_2b&

kill:
	killall -q Exercise11_2a
	killall -q Exercise11_2b
