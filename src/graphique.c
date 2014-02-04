#include "../include/graphique.h"

BOUTONS placer_boutons(SDL_Surface* ecran, BOUTONS lesboutons) {
	
	lesboutons.boutonoui = IMG_Load("data/boutonoui.png");
	lesboutons.pos_oui.x  = N*SIZE/2 - lesboutons.boutonoui->w - 50; //un peu en retrait par rapport au milieu de la ligne
	lesboutons.pos_oui.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.boutonoui, NULL, ecran, &(lesboutons.pos_oui));

	lesboutons.boutonnon = IMG_Load("data/boutonnon.png");
	lesboutons.pos_non.x  = N*SIZE/2 + lesboutons.boutonnon->w/2 - 50;
	lesboutons.pos_non.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.boutonnon, NULL, ecran, &(lesboutons.pos_non));

	SDL_Flip(ecran);

	return lesboutons;
}

BOUTONS placer1bouton(SDL_Surface* ecran, BOUTONS lebouton) {
	printf("entrée dans placer1bouton\n");
	
	lebouton.boutonoui = IMG_Load("data/boutonok.png");
	lebouton.pos_oui.x  = N*SIZE/2 - lebouton.boutonoui->w/2;
	lebouton.pos_oui.y = N*SIZE - 1.2*lebouton.boutonoui->h;
	SDL_BlitSurface(lebouton.boutonoui, NULL, ecran, &(lebouton.pos_oui));

	SDL_Flip(ecran);

	return lebouton;
}

int clique_recommence(BOUTONS lesboutons) {

	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
	
	int choix = 14;
	SDL_Event event;

	while (choix == 14) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				return -14;
				break;
				
			case SDL_MOUSEBUTTONUP:
				//pour valider le clic il faut que
				//le bouton soit le gauche
				//le curseur se trouve sur un des boutons de choix
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x > lesboutons.pos_oui.x && event.button.x < lesboutons.pos_oui.x + lesboutons.boutonoui->w &&
					event.button.y > lesboutons.pos_oui.y && event.button.y < lesboutons.pos_oui.y + lesboutons.boutonoui->h)
					{
					choix = 1;
				}
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x > lesboutons.pos_non.x && event.button.x < lesboutons.pos_non.x + lesboutons.boutonnon->w &&
					event.button.y > lesboutons.pos_non.y && event.button.y < lesboutons.pos_non.y + lesboutons.boutonnon->h)
					{
					choix = 0;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_o:
						choix = 1;
						break;
					case SDLK_n:
						choix = 0;
						break;
					case SDLK_RETURN:
						choix = 1;
						break;
					case SDLK_KP_ENTER:
						choix = 1;
						break;

					default: break;
				}

			default: break;
		}
	}

	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);

	return choix;
}

int clique_ok(BOUTONS lesboutons) {
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
	
	int choix = 14;
	SDL_Event event;

	while (choix == 14) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				return -14;
				break;
				
			case SDL_MOUSEBUTTONUP:
				//pour valider le clic il faut que
				//le bouton soit le gauche
				//le curseur se trouve sur le bouton OK
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x > lesboutons.pos_oui.x && event.button.x < lesboutons.pos_oui.x + lesboutons.boutonoui->w &&
					event.button.y > lesboutons.pos_oui.y && event.button.y < lesboutons.pos_oui.y + lesboutons.boutonoui->h)
					{
					choix = 0;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_KP_ENTER:
						choix = 0;
						break;

					case SDLK_RETURN:
						choix = 0;
						break;
						
					default: break;
				}

			default: break;
		}
	}

	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);

	return choix;
}
