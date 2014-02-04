#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

//la structure des scores
typedef struct {
	int position;		//classement dans la liste
	char player[25];
	int resultat;		//nombre de points obtenus
} SCORE;

int SIZE;	//taille d'une case
int N;		//nombre de cases du tableau
int UT;		//base de temps en ms


#endif
