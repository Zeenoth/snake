#ifndef _INIT_H_
#define _INIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "fichier.h"
#include "liste.h"
#include "fonctions.h"
#include "global.h"


//fonction qui initialise la SDL et crée la fenêtre du jeu
SDL_Surface* init_SDL(SDL_Surface* ecran, int taille_fenetre);

//fonction qui place le tout premier pois en veillant à ce qu'il ne coïncide pas avec le serpent
POIS init_pois(POIS p, SERPENT s);

//fonction qui initialise le serpent : trois cases vers la gauche en partant du centre de l'écran
SERPENT init_serpent(SERPENT le_serpent, int taille_serpent);

//fonction qui alloue le tableau contenant les meilleurs scores et l'initialise
SCORE* init_scores(void);

//fonction qui quitte la SDL et vide la mémoire
void quit(SERPENT s);











#endif
