#include "../include/graphique.h"

BOUTONS placer_boutons(SDL_Surface* ecran, BOUTONS lesboutons) {
	
	lesboutons.boutonoui = IMG_Load("sprites/boutonoui.png");
	lesboutons.pos_oui.x  = N*SIZE/2 - lesboutons.boutonoui->w - 50; //un peu en retrait par rapport au milieu de la ligne
	lesboutons.pos_oui.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.boutonoui, NULL, ecran, &(lesboutons.pos_oui));

	lesboutons.boutonnon = IMG_Load("sprites/boutonnon.png");
	lesboutons.pos_non.x  = N*SIZE/2 + lesboutons.boutonnon->w/2 - 50;
	lesboutons.pos_non.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.boutonnon, NULL, ecran, &(lesboutons.pos_non));

	SDL_Flip(ecran);

	return lesboutons;
}
