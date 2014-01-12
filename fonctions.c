#include "liste.h"

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



SDL_Surface* creer_fenetre(int largeur, int hauteur) {
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

	return fenetre;
}

void placer_pois(POIS* p, int H, int W) {
	srand(time(NULL));
	int x=rand()%W;
	int y=rand()%H;
	
	p->abscisse=x;
	p->ordonnee=y;
	
	//affiche_case(x,y) pour mettre  le sprite du pois dans la case x,y
}

int cogne_mur(SERPENT s, int H, int W) {
	if (s->coord.abscisse<0 || s->coord.ordonnee<0 || s->coord.abscisse>W-1 || s->coord.ordonnee>H-1) {
		return 0;
	}
	else return 1;
}

void visualiser_pois(POIS p) {
	printf("abscisse %d, ordonnée %d\n", p.abscisse, p.ordonnee);
}

SERPENT grandit(SERPENT s) {
	//création du maillon qui sera la tête
	Maillon tete;
	tete.n = (s->n)+1; //mise à jour de la taille du serpent

	//pour connaître les coordonnées de la nouvelle tête, il faut savoir dans quelle direction le serpent avance
	switch(s->direction) {
		case droite:
			tete.coord.abscisse = s->coord.abscisse +1;
			tete.coord.ordonnee = s->coord.ordonnee;
			break;
		case gauche:
			tete.coord.abscisse = s->coord.abscisse -1;
			tete.coord.ordonnee = s->coord.ordonnee;
			break;
		case haut:
			tete.coord.abscisse = s->coord.abscisse;
			tete.coord.ordonnee = s->coord.ordonnee -1;
			break;
		case bas:
			tete.coord.abscisse = s->coord.abscisse;
			tete.coord.ordonnee = s->coord.ordonnee +1;
			break;
	}

	//le serpent avance dans la même direction qu'avant donc
	tete.direction = s->direction;

	s = ajout_tete(tete,s);

	return s;
}













	
