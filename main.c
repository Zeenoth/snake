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
#include "controle.h"


int main(int argc, char* argv[]) {

/*******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE

SDL_Surface* ecran = NULL;
int taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);

/******************************************************************/
		//CRÉATION DU SERPENT

printf("\ncréer le serpent\n");

//taille initiale du serpent
int taille_serpent = 4;

SERPENT leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent);
printf("serpent initialisé : \n");
visualiser_liste(leserpent);

/******************************************************************/
		//PLACEMENT DU POIS

printf("\nplacer le pois\n");
srand(time(NULL)); //initialisation de la fonction random
POIS lepois;
lepois = init_pois(lepois, leserpent);
visualiser_pois(lepois);

/******************************************************************/
		//VARIABLES UTILES POUR LE PROGRAMME

VARIABLES var;
var.partie_finie = 0; //vaut 0 tant que le joueur n'a pas perdu ni quitté le jeu, 1 sinon
var.score = 0; //compte le nombre de pois mangés par le serpent

printf("\nFIN DE L'INITIALISATION\n\n");

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

//chargement des sprites
SDL_Surface* pomme = NULL;
pomme = IMG_Load("sprites/apple60.jpg");

SDL_Surface* tete = NULL;
tete = IMG_Load("sprites/corps.png");

rafraichir(ecran, tete, leserpent, pomme, lepois);

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

var = controle(ecran, leserpent, lepois, tete, pomme, var);
printf("ton score : %d\n", var.score);
	
/******************************************************************/
	return 0;
}
