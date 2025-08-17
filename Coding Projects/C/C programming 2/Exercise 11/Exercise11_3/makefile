

CC=gcc

CFLAGS+=-Wall -g

OBJECTS=

all: Exercise11_3a.c Exercise11_3b.c
	$(CC) $(CFLAGS) Exercise11_3a.c -o Exercise11_3a -lpthread 
	$(CC) $(CFLAGS) Exercise11_3b.c -o Exercise11_3b -lpthread 


clean:
	rm -f *~
	rm -f *.o
	rm -f Exercise11_3a
	rm -f Exercise11_3b

run:
	rm -f FIFO_AB
	rm -f FIFO_BA
	touch FIFO_AB
	touch FIFO_BA
	./Exercise11_3a&
	./Exercise11_3b&

kill:
	killall -q Exercise11_3a
	killall -q Exercise11_3b
