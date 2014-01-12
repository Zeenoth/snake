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

#include "liste.h"
#include "fonctions.h"

//fonction qui place le tout premier pois
POIS init_pois(POIS p, int hauteur, int largeur);

//fonction qui initialise le serpent : trois cases vers la gauche en partant du centre de l'écran
SERPENT init_serpent(SERPENT le_serpent, int taille_serpent, int hauteur, int largeur);












#endif
