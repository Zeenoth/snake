#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "fonctions.h"

void creer_fenetre(int largeur, int hauteur) {
	SDL_Surface* fenetre=NULL;

	fenetre = SDL_SetVideoMode(largeur,hauteur, 16, SDL_HWSURFACE );
	if( fenetre == NULL ) {
	        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
		exit(0);
    	}   
	SDL_WM_SetCaption("snake",NULL); //pour lui donner un nom

	printf("coloriage en blanc de la fenêtre graphique\n");	
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));

	SDL_Flip(fenetre);
}

void placer_pois(POIS* p, int H, int W) {
	srand(time(NULL));
	int x=rand()%W;
	int y=rand()%H;
	
	p->abs=x;
	p->ord=y;
	
	//affiche_case(x,y) pour mettre  le sprite du pois dans la case x,y
}

int cogne_mur(SERPENT s, int H, int W) {
	if (s.abs_serp<0 || s.ord_serp<0 || s.abs_serp>W-1 || s.ord_serp>H-1) {
		return 0;
	}
	else return 1;
}














	
