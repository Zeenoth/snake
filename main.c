#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "liste.h"
#include "fonctions.h"
#include "init.h"

#define N 15 //taille d'une case
#define UT 500 //base de temps en ms


int main(int argc, char* argv[]) {

/******************************************************************/
// contrôle des arguments passés en ligne de commande
if (argc!=3) {
	printf("Il faut entrer deux paramètres entiers : le nombre de lignes du tableau et le nombre de colonnes\n");
	exit(0);
}

//nombre de cases en hauteur
	int H=atoi(argv[1]);
	printf("nombre de lignes : %d\n", H);
//nombre de cases en largeur
	int W=atoi(argv[2]);
	printf("nombre de colonnes : %d\n", W);


/******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE


if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) == -1) {
	printf("Impossible d'initialiser la SDL: %s.\n", SDL_GetError());
       	SDL_Quit();
}

SDL_Surface* ecran = NULL;
ecran = creer_fenetre(500,500);

/******************************************************************/
		//PLACEMENT DU POIS

printf("placer le pois\n");

POIS lepois;
lepois = init_pois(lepois, H, W);
visualiser_pois(lepois);

/******************************************************************/
		//CRÉATION DU SERPENT

printf("créer le serpent\n");

//taille initiale du serpent
int taille_serpent = 3;

SERPENT leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent, H, W);
printf("serpent initialisé : \n");
visualiser_liste(leserpent);

/******************************************************************/
	

	return 0;
}
