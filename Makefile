DIRSDL=/users/prog1a/C/librairie/2011
CFLAGS=-g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include
LDFLAGS=-L$(DIRSDL)/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw

All: main.o liste.o fonctions.o init.o
	gcc main.o liste.o fonctions.o init.o -o l $(LDFLAGS) $(CFLAGS)

main.o: main.c
	gcc -c main.c -o main.o $(CFLAGS)

init.o: init.c
	gcc -c init.c -o init.o $(CFLAGS)

#lecture.o: lecture.c
#	gcc -c lecture.c -o lecture.o $(OPT) $(SDL)

#structures.o: structures.c
#	gcc -c structures.c -o structures.o $(OPT) $(SDL)

liste.o: liste.c
	gcc -c liste.c -o liste.o $(CFLAGS)

fonctions.o:  fonctions.c
	gcc -c fonctions.c -o fonctions.o $(CFLAGS)


#prim.o: prim.c
#	gcc -c prim.c -o prim.o $(OPT) $(SDL)

clean:
	rm -r *.o

mrproper:
	rm -r *.o
	rm -r l
	rm -r *~
