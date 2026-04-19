game: main.o ennemi.o
	gcc main.o ennemi.o -o game -lSDL2 -lSDL2_image

main.o: main.c
	gcc -c main.c

ennemi.o: ennemi.c
	gcc -c ennemi.c

clean:
	rm -f *.o game
