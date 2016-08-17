CC := gcc
CFLAGS := -W -Wall -g -ggdb

SRC =				\
	src/rikudo_stack.c	\
	src/rikudo_grid.c	\
	src/rikudo_x.c		\
	src/rikudo_read.c	\
	src/rikudo_ia.c		\
	src/rikudo_reverse.c	\
	src/rikudo_play.c	\
	src/rikudo.c

RIKUDO := rikudo

OBJ = $(SRC:.c=.o)

$(RIKUDO): $(OBJ)
	$(CC) $(OBJ) -o $(RIKUDO) -lncurses -lX11 -lXtst -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) $(OBJ)
