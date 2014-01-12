#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "liste.h"
#include "fonctions.h"
#include "init.h"
#include "global.h"


int main(int argc, char* argv[]) {

/*******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE

SDL_Surface* ecran = NULL;
int taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);
getchar();

/******************************************************************/
		//PLACEMENT DU POIS

printf("placer le pois\n");

POIS lepois;
lepois = init_pois(lepois);
visualiser_pois(lepois);

/******************************************************************/
		//CRÉATION DU SERPENT

printf("créer le serpent\n");

//taille initiale du serpent
int taille_serpent = 3;

SERPENT leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent);
printf("serpent initialisé : \n");
visualiser_liste(leserpent);

/******************************************************************/
		//VARIABLES UTILES POUR LE PROGRAMME

int partie_finie = 0; //vaut 0 tant que le joueur n'a pas perdu ni quitté le jeu, 1 sinon
int score = 0; //compte le nombre de pois mangés par le serpent

printf("\nFIN DE L'INITIALISATION\n\n");

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

//chargement des sprites
SDL_Surface* pomme = NULL;
SDL_Rect positionpomme;
pomme = IMG_Load("sprites/apple32x32.jpg");
positionpomme.x = (lepois.abscisse*SIZE); //le sprite n'est pas encore bien centré sur la case !
positionpomme.y = (lepois.ordonnee*SIZE);
SDL_BlitSurface(pomme, NULL, ecran, &positionpomme);
SDL_Flip(ecran);
getchar();

SDL_Surface* tete = NULL;
SDL_Rect positiontete;
tete = IMG_Load("sprites/corps70x65.jpg");
positiontete.x = (leserpent->coord.abscisse) * SIZE;
positiontete.y = (leserpent->coord.ordonnee) * SIZE;
SDL_BlitSurface(tete, NULL, ecran, &positiontete);
SDL_Flip(ecran);
getchar();

SDL_Surface* corps = NULL;

/*Tant que la partie n'est pas finie :
 *	le serpent avance d'une case par unité de temps
 *	si on appuie sur une flèche du clavier, il change de direction pour le mouvement suivant
 * 	si la tête arrive sur la case du pois :
 * 		score = score + 1
 * 		le serpent grandit
 * 		on place un nouveau pois
 * 	si le serpent se mange tout seul ou s'il se cogne contre le bord de l'écran, la partie est finie
 *
 * Si la partie est finie :
 * 	afficher le score
 * 	s'il fait partie des dix meilleurs, demander le nom du joueur et l'ajouter dans le tableau
 * 	afficher le tableau des scores
 */
	
/******************************************************************/
	return 0;
}
