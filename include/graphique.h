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
	SDL_Surface* boutonoui;
	SDL_Rect pos_oui;
	SDL_Surface* boutonnon;
	SDL_Rect pos_non;
} BOUTONS;			//structure qui contient les deux boutons pour choisir si on veut recommencer une partie

BOUTONS placer_boutons(SDL_Surface* ecran, BOUTONS lesboutons);


#endif
