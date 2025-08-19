
SRCS = $(wildcard Exercise7_?.c)

PROGS = $(patsubst %.c,%,$(SRCS))

CFLAGS+=-Wall -g

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $< -lm

clean:
	rm -f *~
	rm -f $(PROGS)

