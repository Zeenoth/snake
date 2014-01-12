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
#include "global.h"


int main(int argc, char* argv[]) {

/*******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE

SDL_Surface* ecran = NULL;
int taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);
getchar();

/******************************************************************/
		//PLACEMENT DU POIS

printf("placer le pois\n");

POIS lepois;
lepois = init_pois(lepois);
visualiser_pois(lepois);

/******************************************************************/
		//CRÉATION DU SERPENT

printf("créer le serpent\n");

//taille initiale du serpent
int taille_serpent = 3;

SERPENT leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent);
printf("serpent initialisé : \n");
visualiser_liste(leserpent);

printf("\nFIN DE L'INITIALISATION\n\n");

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL



	
/******************************************************************/
	return 0;
}
