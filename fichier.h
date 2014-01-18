#ifndef _FICHIER_H_
#define _FICHIER_H_

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "liste.h"
#include "fonctions.h"
#include "init.h"
#include "global.h"
#include "controle.h"


//la structure des scores
typedef struct {
	int position;
	char player[25];
	int resultat;
} SCORE;


//fonction qui charge le fichier en mémoire
SCORE* charge_scores(FILE* fichier, SCORE* tab);

//affiche dans le terminal les meilleurs scores
int affiche_scores(SCORE* t);



#endif
