OUT = Exercise6_4
CC = gcc
ODIR = ../obj
SDIR = .
INC = -I../include
CFLAGS+=-Wall -g

_OBJSTOBUILD = Game.o  
OBJSTOBUILD = $(patsubst %,$(ODIR)/%,$(_OBJSTOBUILD))

_OBJS = Item.o Location.o Player.o ItemList.o $(_OBJSTOBUILD)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	gcc $(CFLAGS) $(INC) $^ main.c -o $(OUT) 

.PHONY: clean

clean:
	rm -f $(OBJSTOBUILD) $(OUT)