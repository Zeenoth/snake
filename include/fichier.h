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


//fonction qui charge le fichier en mémoire
SCORE* charge_scores(FILE* fichier, SCORE* tab);

//affiche dans le terminal les meilleurs scores
int affiche_scores(SCORE* t);

//regarde si le joueur fait partie des meilleurs ; renvoie le classement du joueur
int merite(int s, SCORE* t);

//inscrit le score du joueur dans le fichier
void ecrit_score(int classement, int points, FILE* fichier, SCORE* tableau);



#endif
