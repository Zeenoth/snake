#ifndef _CONTROLE_H_
#define _CONTROLE_H_

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
#include "init.h"
#include "global.h"
#include "controle.h"
#include "fichier.h"
#include "fonctions.h"

#ifndef _TEXTE_
#define _TEXTE_
//Structure utile pour l'affichage du texte
typedef struct {
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Rect pos;	//la position
} TEXTE;
#endif

typedef struct {
	int partie_finie;	//indique si l'on doit sortir de la boucle
	int score;
	int continuer;		//indique si l'on doit sortir de la boucle
	int queue;		//indique si le serpent s'est mordu la queue
	int mange;		//indique s'il a mangé le pois
	int flag;		//s'il a mangé le pois, on met un flag pour s'en souvenir au prochain tour de boucle
	int cogne;		//indique s'il s'est pris un mur
} VARIABLES;

VARIABLES controle(SDL_Surface* ecran, SERPENT leserpent, POIS lepois, SDL_Surface* corps, SDL_Surface* pomme, VARIABLES variables, TEXTE lescore);

//fonction qui fait déplacer le serpent : dans le cas général, il avance dans la bonne direction ;
//s'il a mangé la pomme il faut aussi qu'il grandisse.
//passage par pointeur pour le serpent, car la fonction peut pas tout renvoyer ! À moins de rentrer le serpent
//dans la structure VARIABLES...
VARIABLES bouge(SERPENT *s, POIS p, VARIABLES variables);





#endif
