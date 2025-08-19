OUT = Exercise6_3
CC = gcc
ODIR = ../obj
SDIR = .
INC = -I../include
CFLAGS+=-Wall -g

_OBJSTOBUILD = Location.o Player.o 
OBJSTOBUILD = $(patsubst %,$(ODIR)/%,$(_OBJSTOBUILD))

_OBJS = Item.o ItemList.o $(_OBJSTOBUILD)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) main.c
	gcc $(CFLAGS) $(INC) $^ -o $(OUT) 

.PHONY: clean

clean:
	rm -f $(OBJSTOBUILD) $(OUT)