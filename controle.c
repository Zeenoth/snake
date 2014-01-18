#include "controle.h"

VARIABLES controle(SDL_Surface* ecran, SERPENT leserpent, POIS lepois, SDL_Surface* corps, SDL_Surface* pomme, VARIABLES variables) {

	printf("\nentrée dans la fonction controle\n");
	
	int continuer = 1;
	SDL_Event event;
	int mange; //s"il mange le pois
	int cogne; //s'il se cogne contre un mur
	int queue; //s'il se mord la queue

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
						if (leserpent->direction != bas) {
							leserpent->direction = haut;
							leserpent = avance(leserpent);
						}
						break;

					case SDLK_DOWN:
						if (leserpent->direction != haut) {
							leserpent->direction = bas;
							leserpent = avance(leserpent);
						}
						break;

					case SDLK_RIGHT:
						if (leserpent->direction != gauche) {
							leserpent->direction = droite;
							leserpent = avance(leserpent);
						}
						break;

					case SDLK_LEFT:
						if (leserpent->direction != droite) {
							leserpent->direction = gauche;
							leserpent = avance(leserpent);
						}
						break;
				}
			
		}

		//printf("sortie du switch\n");
		
		//on regarde si le serpent a mangé la pomme
		mange = mange_pois(leserpent, lepois);
		if (mange == 1) {
			leserpent = grandit(leserpent);
			lepois = init_pois(lepois, leserpent);
			variables.score++;
		}

		//on regarde s'il s'est pris un mur
		cogne = cogne_mur(leserpent, N, N);
		if (cogne == 1) {
			printf("\nperdu !\n");
			variables.partie_finie = 1;
			continuer = 0;
			return variables;
		}

		//on regarde s'il se mord la queue
		queue = mange_serpent(leserpent);
		if (queue == 1) {
			printf("\nperdu !\n");
			variables.partie_finie = 1;
			continuer = 0;
			return variables;
		}
		
		rafraichir(ecran, corps, leserpent, pomme, lepois);

		
	}

	


	
	return variables;
}
