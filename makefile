OPT= -Wall -pipe 
SDL= -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_draw


All: main.o liste.o fonctions.o init.o controle.o
	gcc main.o liste.o fonctions.o init.o controle.o -o l $(OPT) $(SDL)

main.o: main.c
	gcc -c main.c -o main.o $(OPT) $(SDL)

init.o: init.c
	gcc -c init.c -o init.o $(OPT) $(SDL)

controle.o: controle.c
	gcc -c controle.c -o controle.o $(OPT) $(SDL)

liste.o: liste.c
	gcc -c liste.c -o liste.o $(OPT) $(SDL)

fonctions.o:  fonctions.c
	gcc -c fonctions.c -o fonctions.o $(OPT) $(SDL)


#prim.o: prim.c
#	gcc -c prim.c -o prim.o $(OPT) $(SDL)

clean:
	rm -r *.o

mrproper:
	rm -r *.o
	rm -r l
	rm -r *~

	
