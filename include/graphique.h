#ifndef _GRAPHIQUE_H_
#define _GRAPHIQUE_H_

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
#include "controle.h"
#include "fichier.h"

/********************************************************************/
// 	FONCTIONS RELATIVES AUX MENUS DANS LA FENÊTRE
/********************************************************************/

typedef struct {
	SDL_Surface* bouton1;
	SDL_Rect pos_1;
	SDL_Surface* bouton2;
	SDL_Rect pos_2;
	SDL_Surface* bouton3;
	SDL_Rect pos_3;
} BOUTONS;	//structure qui contient 3 boutons

//place graphiquement les deux boutons "oui" et "non" à la fin de la partie
BOUTONS placer_boutons(SDL_Surface* ecran, BOUTONS lesboutons);

//place graphiquement le bouton "OK" en dessous du tableau des scores
BOUTONS placer1bouton(SDL_Surface* ecran, BOUTONS lebouton);

//renvoie 1 si le joueur clique sur "oui", 0 s'il clique sur "non"
int clique_recommence(BOUTONS lesboutons);

//renvoie 0 si le joueur clique sur "OK"
int clique_ok(BOUTONS lesboutons);

//renvoie le numéro du bouton cliqué ; on peut aussi les sélectionner au clavier
int clique_menu(int* jaichoisi, int choix);


#endif
