#include "init.h"
#include "liste.h"
#include "fonctions.h"

#include <time.h>
#include <stdlib.h>

SDL_Surface* init_SDL(SDL_Surface* ecran, int taille_fenetre) {
	if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) == -1) {
		printf("Impossible d'initialiser la SDL: %s.\n", SDL_GetError());
		SDL_Quit();
	}

	ecran = creer_fenetre(taille_fenetre, taille_fenetre);

	return ecran;
}

POIS init_pois(POIS p) {
	
	srand(time(NULL)); //initialisation de la fonction random
	
	p.abscisse=rand()%SIZE;
	p.ordonnee=rand()%SIZE;

	return p;
}

SERPENT init_serpent(SERPENT le_serpent, int taille_serpent) {
	le_serpent = calloc(1, sizeof(*le_serpent));
	if (le_serpent == NULL) {
		printf("erreur d'initialisation\n");
		exit(0);
	}

	le_serpent->n = 1;
	le_serpent->direction = droite; //en début de partie il commence vers la droite
	le_serpent->coord.abscisse = floor(SIZE/2); //il apparaît au centre de l'écran
	le_serpent->coord.ordonnee = floor(SIZE/2);

	while (le_serpent->n < taille_serpent) {
		le_serpent = grandit(le_serpent);
		//la fonction grandit() incrémente serpent->n
	}

	return le_serpent;
}