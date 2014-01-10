#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

//#include "structures.h"
#include "fonctions.h"

int main(int argc, char* argv[]) {

/******************************************************************/
//nombre de cases en hauteur
	//int H=atoi(argv[1]);
	//printf("nombre de lignes du tableau : %d\n", H);
//nombre de cases en largeur
	//int W=atoi(argv[2]);
	//printf("nombre de colonnes du tableau : %d\n", W);

/******************************************************************/
		//INITIALISATION


if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) == -1) {
	printf("Impossible d'initialiser la SDL: %s.\n", SDL_GetError());
       	SDL_Quit();
}
       
creer_fenetre(500,500);
//getchar();

/******************************************************************/
//placer le pois
	POIS p;
	p.abs=1;
	p.ord=2;
	voir_pois(p);
	struct POIS* point=NULL;
	point=&p;
	placer_pois(point, 50, 50);
	voir_pois(p);

//créer le serpent
	SERPENT serpent;
	serpent.n=3;
	serpent.abs_serp=49;
	serpent.ord_serp=13;
//initialisation des positions du serpent
	


	int a;
	a=cogne_mur(serpent, 50, 50);
	printf("%d\n", a);


/******************************************************************/
	COORDONNEES c;
	/*c=calloc(1, sizeof(*c));
	if (c==NULL) {
		printf("erreur\n");
		exit(0);
	}*/
	c.abs=4;
	c.ord=5;

	voir_coord(c);

	COORDONNEES c2;
	c2.abs=45;
	c2.ord=4;
	voir_coord(c2);

	LISTE_POS l=creer_liste();
	l=ajouter_queue(c, l);
	l=ajouter_queue(c2, l);
	voir_liste(l);

	return 0;
}
