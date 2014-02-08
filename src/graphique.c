#include "../include/graphique.h"

BOUTONS placer_boutons(SDL_Surface* ecran, BOUTONS lesboutons) {
	
	lesboutons.bouton1 = IMG_Load("data/boutonoui.png");
	lesboutons.pos_1.x  = N*SIZE/2 - lesboutons.bouton1->w - 50; //un peu en retrait par rapport au milieu de la ligne
	lesboutons.pos_1.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.bouton1, NULL, ecran, &(lesboutons.pos_1));

	lesboutons.bouton2 = IMG_Load("data/boutonnon.png");
	lesboutons.pos_2.x  = N*SIZE/2 + lesboutons.bouton2->w/2 - 50;
	lesboutons.pos_2.y = N*SIZE/2;
	SDL_BlitSurface(lesboutons.bouton2, NULL, ecran, &(lesboutons.pos_2));

	SDL_Flip(ecran);

	return lesboutons;
}

BOUTONS placer1bouton(SDL_Surface* ecran, BOUTONS lebouton) {
	printf("entrée dans placer1bouton\n");
	
	lebouton.bouton1 = IMG_Load("data/boutonok.png");
	lebouton.pos_1.x  = N*SIZE/2 - lebouton.bouton1->w/2;
	lebouton.pos_1.y = N*SIZE - 1.2*lebouton.bouton1->h;
	SDL_BlitSurface(lebouton.bouton1, NULL, ecran, &(lebouton.pos_1));

	lebouton.bouton2 = NULL;
	lebouton.bouton3 = NULL;

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
					event.button.x > lesboutons.pos_1.x && event.button.x < lesboutons.pos_1.x + lesboutons.bouton1->w &&
					event.button.y > lesboutons.pos_1.y && event.button.y < lesboutons.pos_1.y + lesboutons.bouton1->h)
					{
					choix = 1;
				}
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x > lesboutons.pos_2.x && event.button.x < lesboutons.pos_2.x + lesboutons.bouton2->w &&
					event.button.y > lesboutons.pos_2.y && event.button.y < lesboutons.pos_2.y + lesboutons.bouton2->h)
					{
					choix = 0;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						return -14;
						break;
						
					case SDLK_o:
						choix = 1;
						break;
					case SDLK_n:
						choix = 0;
						break;
					case SDLK_BACKSPACE:
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
					event.button.x > lesboutons.pos_1.x && event.button.x < lesboutons.pos_1.x + lesboutons.bouton1->w &&
					event.button.y > lesboutons.pos_1.y && event.button.y < lesboutons.pos_1.y + lesboutons.bouton1->h)
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

int clique_menu(int* jaichoisi, int choix) {
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

/*Si le joueur appuie sur haut, choix--
 * si choix<1 alors choix=dernière possibilité
 * la fonction renvoie le numéro du choix dès que le joueur appuie sur haut ou bas
 * si on a validé son choix, jaichoisi va prendre la valeur 1 et on lance le programme principal
 * */
 
	int continuer = 1;
	SDL_Event event;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				*jaichoisi = -14;
				continuer = 0;
				break;
				
			/*case SDL_MOUSEBUTTONUP:
				//pour valider le clic il faut que
				//le bouton soit le gauche
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x > lesboutons.pos_1.x && event.button.x < lesboutons.pos_1.x + lesboutons.bouton1->w &&
					event.button.y > lesboutons.pos_1.y && event.button.y < lesboutons.pos_1.y + lesboutons.bouton1->h)
					{
					choix = 0;
				}
				break;*/

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						*jaichoisi = -14;
						continuer = 0;
						break;
						
					case SDLK_KP_ENTER:
						*jaichoisi = 1;
						continuer = 0;
						printf("%d\n", *jaichoisi);
						break;

					case SDLK_RETURN:
						*jaichoisi = 1;
						continuer = 0;
						printf("%d\n", *jaichoisi);
						break;

					case SDLK_UP:
						choix--;
						continuer = 0;
						break;

					case SDLK_DOWN:
						choix++;
						continuer = 0;
						break;
						
					default: break;
				}

			default: break;
		}
	}
	if (choix < 1) {
		choix = 4;
	}
	if (choix > 4) {
		choix = 1;
	}

	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);

	return choix;
}








