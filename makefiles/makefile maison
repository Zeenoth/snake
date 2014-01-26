OPT= -Wall -pipe 
SDL= -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_draw


All: main.o liste.o fonctions.o init.o controle.o fichier.o graphique.o
	gcc main.o liste.o fonctions.o init.o controle.o fichier.o graphique.o -o l $(OPT) $(SDL)

main.o: src/main.c
	gcc -c src/main.c -o main.o $(OPT) $(SDL)

fichier.o: src/fichier.c
	gcc -c src/fichier.c -o fichier.o $(OPT) $(SDL)

init.o: src/init.c
	gcc -c src/init.c -o init.o $(OPT) $(SDL)

controle.o: src/controle.c
	gcc -c src/controle.c -o controle.o $(OPT) $(SDL)

liste.o: src/liste.c
	gcc -c src/liste.c -o liste.o $(OPT) $(SDL)

fonctions.o:  src/fonctions.c
	gcc -c src/fonctions.c -o fonctions.o $(OPT) $(SDL)

graphique.o: src/graphique.c
	gcc -c src/graphique.c -o graphique.o $(OPT) $(SDL)

clean:
	rm -r *.o

mrproper:
	rm -r *.o
	rm -r l
	rm -r *~

	
