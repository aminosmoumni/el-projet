prog: main.o menu.o
	gcc main.o menu.o -o prog -lSDL2 -lSDL2_image -lSDL2_mixer


main.o: main.c menu.h
	gcc -c main.c


menu.o: menu.c menu.h
	gcc -c menu.c
