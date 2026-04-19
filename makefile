# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra

# Libraries
LIBS = -lSDL2 -lSDL2_image

# Files
SRC = main.c background.c
OBJ = $(SRC:.c=.o)

# Executable
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXEC)

re: fclean all
