#include "controle.h"

VARIABLES controle(SDL_Surface* ecran, SERPENT leserpent, POIS lepois, SDL_Surface* corps, SDL_Surface* pomme, VARIABLES variables) {

	printf("\nentrée dans la fonction controle\n");
	
	int continuer = 1;
	SDL_Event event;
	int mange;

	//BOUCLE DE LA GESTION DES ÉVÈNEMENTS
	while (continuer) {

		//on attend que le joueur appuie sur une touche
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					
					case SDLK_UP:
						leserpent->direction = haut;
						leserpent = avance(leserpent);
						break;

					case SDLK_DOWN:
						leserpent->direction = bas;
						leserpent = avance(leserpent);
						break;

					case SDLK_RIGHT:
						leserpent->direction = droite;
						leserpent = avance(leserpent);
						break;

					case SDLK_LEFT:
						leserpent->direction = gauche;
						leserpent = avance(leserpent);
						break;
				}
			
		}

		//printf("sortie du switch\n");
		
		//on regarde si le serpent a mangé la pomme
		mange = mange_pois(leserpent, lepois);
		//printf("score %d\n", variables.score);
		if (mange == 1) {
			leserpent = grandit(leserpent);
			lepois = init_pois(lepois, leserpent);
			variables.score++;
		}
		rafraichir(ecran, corps, leserpent, pomme, lepois);

		
	}

	


	
	return variables;
}
