#ifndef _FONCTIONS_H_

#define _FONCTIONS_H_

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "liste.h"
#include "init.h"


//ouverture d'une fenêtre graphique blanche
SDL_Surface* creer_fenetre(int largeur, int hauteur);

//fonction qui place un pois (l'affichage n'est pas encore pris en compte ; à la fin la fonction retournera void)
void placer_pois(POIS* p, int H, int W);

//fonction qui teste si le serpent s'est pris un mur. Retourne 1 si le serpent ne s'est pas cogné et 0 si oui
int cogne_mur(SERPENT s, int H, int W);

void visualiser_pois(POIS p);

SERPENT grandit(SERPENT s);

#endif
