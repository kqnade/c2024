CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lncurses

SRC = src/main.c src/game.c src/words.c src/ui.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = wordle_game

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

