OUT = Exercise6_2
CC = gcc
ODIR = ../obj
SDIR = .
INC = -I../include
CFLAGS+=-Wall -g

_OBJS = ItemList.o 
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) main.c
	gcc $(CFLAGS) $(INC) $^ -o $(OUT)

.PHONY: clean

clean:
	rm -f $(OBJS) $(OUT)