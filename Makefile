CC := gcc
CFLAGS := -W -Wall -g -ggdb

INCLUDES =					\
	-I src/					\
	-I src/reverse				\
	-I src/X/				\
	-I src/profil				\

SRC =						\
	src/X/rikudo_x.c			\
	src/X/rikudo_play.c			\
	src/reverse/rikudo_reverse.c		\
	src/profil/rikudo_cycle.c		\
	src/profil/rikudo_stat.c		\
	src/rikudo_ia.c				\
	src/rikudo_stack.c			\
	src/rikudo_grid.c			\
	src/rikudo_connex.c			\
	src/rikudo.c

RIKUDO := rikudo

OBJ = $(SRC:.c=.o)

$(RIKUDO): $(OBJ)
	$(CC) $(INCLUDES) $(OBJ) -o $(RIKUDO) -lncurses -lX11 -lXtst -lpthread

%.o: %.c
	$(CC) $(INCLUDES) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) $(OBJ)
