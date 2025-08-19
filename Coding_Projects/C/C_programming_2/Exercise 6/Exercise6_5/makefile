OUT = Exercise6_5
CC = gcc
ODIR = ../obj
SDIR = .
INC = -I../include
CFLAGS+=-Wall -g

#_OBJSTOBUILD = Game.o  
#OBJSTOBUILD = $(patsubst %,$(ODIR)/%,$(_OBJSTOBUILD))

_OBJS = Game.o  Item.o Location.o Player.o ItemList.o 
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) main.c
	gcc $(CFLAGS) $(INC) $^ -o $(OUT) 

.PHONY: clean

clean:
	rm -f $(OUT)