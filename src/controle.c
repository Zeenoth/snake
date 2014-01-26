#include "../include/controle.h"

VARIABLES controle(SDL_Surface* ecran, SERPENT leserpent, POIS lepois, SDL_Surface* corps, SDL_Surface* pomme, VARIABLES variables, TEXTE lescore) {

        SDL_Event event;
        int tempsPrecedent = 0;
        int tempsActuel = 0;
        int retour = 0; //drapeau pour éviter que deux appuis différents sur des flèches pendant la même UT ne fassent perdre
        
	fprintf(stdout, "\nAppuie sur une touche pour commencer la partie\n");
	//on décide d'ignorer les mouvements de souris et les relâchements de touches du clavier
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
	SDL_WaitEvent(&event);

        //BOUCLE DE LA GESTION DES ÉVÈNEMENTS
        while (variables.continuer) {
		tempsActuel = SDL_GetTicks();

                SDL_PollEvent(&event);
                
                switch(event.type) {
                        case SDL_QUIT:
                                variables.continuer = 0;
                                variables.partie_finie = 0;
                                return variables;
                                break;

                        case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                                variables.continuer = 0;
                                                variables.partie_finie = 0;
                                                return variables;
                                                break;
                                        
                                        case SDLK_UP:
                                                if (leserpent->direction != bas && retour == 0) {
                                                        leserpent->direction = haut;
                                                }
                                                else {retour =1;}
                                                break;

                                        case SDLK_DOWN:
                                                if (leserpent->direction != haut && retour == 0) {
                                                        leserpent->direction = bas;
                                                }
                                                else {retour = 1;}
                                                break;

                                        case SDLK_RIGHT:
                                                if (leserpent->direction != gauche) {
                                                        leserpent->direction = droite;                                                              
                                                }
                                                else {retour = 1;}
                                                break;

                                        case SDLK_LEFT:
                                                if (leserpent->direction != droite && retour == 0) {
                                                        leserpent->direction = gauche;
                                                }
                                                else {retour = 1;}
                                                break;
                                        default:
                                                break;
                                }
                                default:
                                        break;
                                        
                }
                
if (tempsActuel - tempsPrecedent > UT) {
			bouge(&leserpent, lepois, variables);
			//printf("après bouge, %d\n", leserpent->n);
			variables.flag = 0;
		
		//doit_avancer = 0;

		//on regarde si le serpent a mangé la pomme
		variables.mange = mange_pois(leserpent, lepois);
		//printf("mangé %d\n", variables.mange);
		if (variables.mange == 1) {
			lepois = init_pois(lepois, leserpent);
			//on met un flag pour qu'il grandisse au prochain coup
			variables.flag = 1;
			variables.score++;
			//printf("score %d\n", variables.score);
		}

		//on regarde s'il s'est pris un mur
		variables.cogne = cogne_mur(leserpent, N, N);
		if (variables.cogne == 1) {
			//printf("\nperdu !\n");
			variables.partie_finie = 1;
			variables.continuer = 0;
		}
		
		//on regarde s'il se mord la queue
		variables.queue = mange_serpent(leserpent);
		if (variables.queue == 1) {
			//printf("\nperdu !\n");
			variables.partie_finie = 1;
			variables.continuer = 0;
		}

                rafraichir(ecran, corps, leserpent, pomme, lepois, &lescore, variables.score);
                
tempsPrecedent = tempsActuel;
}
else {retour = 0;}

        }

        SDL_FreeSurface(ecran);
        SDL_FreeSurface(pomme);
        SDL_FreeSurface(corps);

        return variables;
}

VARIABLES bouge(SERPENT *s, POIS p, VARIABLES variables) {
	//printf("flag début bouge %d\n", variables.flag);
	if (variables.flag == 0) {
		 *s = avance(*s);
	 }
	
	if (variables.flag == 1) {
		//printf("ici grandit\n");
		*s = grandit(*s);
		//printf("après grandit, %d\n", (*s)->n);
	}

	
	//printf("flag fin bouge %d\n", variables.flag);

	return variables;
}

