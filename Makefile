prog: main.o minimap.o collisionBB.o collisionPP.o platform.o animation.o
	gcc main.o minimap.o collisionBB.o collisionPP.o platform.o animation.o -o prog -lSDL2 -lSDL2_image

main.o: main.c
	gcc -c main.c

minimap.o: minimap.c
	gcc -c minimap.c

collisionBB.o: collisionBB.c
	gcc -c collisionBB.c

collisionPP.o: collisionPP.c
	gcc -c collisionPP.c

platform.o: platform.c
	gcc -c platform.c

animation.o: animation.c
	gcc -c animation.c

clean:
	rm -f *.o prog
