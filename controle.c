#include "controle.h"

VARIABLES controle(SDL_Surface* ecran, SERPENT leserpent, POIS lepois, SDL_Surface* corps, SDL_Surface* pomme, VARIABLES variables) {

        //printf("\nentrée dans la fonction controle\n");
        
        int continuer = 1;
        SDL_Event event;
        int mange; //s"il mange le pois
        int flag = 0;
        int cogne; //s'il se cogne contre un mur
        int queue; //s'il se mord la queue
        int tempsPrecedent = 0;
        int tempsActuel = 0;

        //BOUCLE DE LA GESTION DES ÉVÈNEMENTS
        while (continuer) {

                //dès que le joueur appuie sur une touche
                SDL_WaitEvent(&event);
                
                switch(event.type) {
                        case SDL_QUIT:
                                continuer = 0;
                                variables.partie_finie = 0;
                                return variables;
                                break;

                        case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                                continuer = 0;
                                                variables.partie_finie = 0;
                                                return variables;
                                                break;
                                        
                                        case SDLK_UP:
                                                if (leserpent->direction != bas) {
                                                        leserpent->direction = haut;
                                                        if (flag == 0) {
                                                                leserpent = avance(leserpent);
                                                        }
                                                        else {
                                                                leserpent = grandit(leserpent);
                                                                flag = 0;
                                                        }
                                                }
                                                break;

                                        case SDLK_DOWN:
                                                if (leserpent->direction != haut) {
                                                        leserpent->direction = bas;
                                                        if (flag == 0) {
                                                                leserpent = avance(leserpent);
                                                        }
                                                        else {
                                                                leserpent = grandit(leserpent);
                                                                flag = 0;
                                                        }
                                                }
                                                break;

                                        case SDLK_RIGHT:
                                                if (leserpent->direction != gauche) {
                                                        leserpent->direction = droite;
                                                        if (flag == 0) {
                                                                leserpent = avance(leserpent);
                                                        }
                                                        else {
                                                                leserpent = grandit(leserpent);
                                                                flag = 0;
                                                        }                                                                
                                                }
                                                break;

                                        case SDLK_LEFT:
                                                if (leserpent->direction != droite) {
                                                        leserpent->direction = gauche;
                                                        if (flag == 0) {
                                                                leserpent = avance(leserpent);
                                                        }
                                                        else {
                                                                leserpent = grandit(leserpent);
                                                                flag = 0;
                                                        }
                                                }
                                                break;
                                        default:
                                                break;
                                }
                                default:
                                        break;
                                        
                }
                

                //tempsActuel = SDL_GetTicks();
                //if (tempsActuel - tempsPrecedent > UT) {
                //        leserpent = avance(leserpent);
                //        tempsPrecedent = tempsActuel;
                //}

                //on regarde si le serpent a mangé la pomme
                        mange = mange_pois(leserpent, lepois);
                        if (mange == 1) {
                                lepois = init_pois(lepois, leserpent);
                                //on met un flag pour qu'il grandisse au prochain coup
                                flag = 1;
                                variables.score++;
                        }

                        //on regarde s'il s'est pris un mur
                        cogne = cogne_mur(leserpent, N, N);
                        if (cogne == 1) {
                                //printf("\nperdu !\n");
                                variables.partie_finie = 1;
                                continuer = 0;
                                return variables;
                        }

                        //on regarde s'il se mord la queue
                        queue = mange_serpent(leserpent);
                        if (queue == 1) {
                                //printf("\nperdu !\n");
                                variables.partie_finie = 1;
                                continuer = 0;
                                return variables;
                        }
                rafraichir(ecran, corps, leserpent, pomme, lepois);
        }

        SDL_FreeSurface(ecran);
        SDL_FreeSurface(pomme);
        SDL_FreeSurface(corps);

        


        
        return variables;
}
