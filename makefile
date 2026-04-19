CC = gcc
CFLAGS = -Wall -Wextra -g
SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_image

SRC = main.c joueur.c
OBJ = $(SRC:.c=.o)
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(SDLFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
