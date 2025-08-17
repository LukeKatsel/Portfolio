
SRCS = $(wildcard Exercise2_?.c)

PROGS = $(patsubst %.c,%,$(SRCS))

CFLAGS+=-Wall -g

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	rm -f *~
	rm -f $(PROGS)

