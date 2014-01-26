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
#include "fichier.h"


int main(int argc, char* argv[]) {

/******************************************************************/
		//VARIABLES UTILES POUR LE PROGRAMME

VARIABLES var;
var.partie_finie = 0; //vaut 0 tant que le joueur n'a pas perdu ni quitté le jeu, 1 sinon
var.score = 0; //compte le nombre de pois mangés par le serpent
var.continuer = 1;
var.mange = 0; //s"il mange le pois
var.flag = 0;
var.cogne = 0; //s'il se cogne contre un mur
var.queue = 0; //s'il se mord la queue
FILE* feuille_scores = NULL;
SCORE* tableau = init_scores(); //alloue et initialise le tableau des scores
SIZE = 70;
N = 10;
UT = 350;

/*******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE


SDL_Surface* ecran = NULL;
int taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);

/******************************************************************/
		//CRÉATION DU SERPENT

printf("\ncréer le serpent\n");

//taille initiale du serpent
int taille_serpent = 3;

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

printf("\nFIN DE L'INITIALISATION\n\n");

/*******************************************************************/
//chargement des sprites
SDL_Surface* pomme = NULL;
pomme = IMG_Load("sprites/apple60.png");

SDL_Surface* tete = NULL;
tete = IMG_Load("sprites/corps.png");

//chargement des textes à afficher
SDL_Color noir = {0, 0, 0};

TEXTE titre;
titre.color = noir;
titre = creer_texte(titre, "sprites/alphawood.ttf", 75, "Bienvenue dans Snake");
titre = positionner_texte(titre, floor(N*SIZE/2 - titre.surface->w/2), floor(N*SIZE/4));

TEXTE instructions;
instructions.color = noir;
instructions = creer_texte(instructions, "sprites/alphawood.ttf", 35, "Appuie sur une touche pour commencer");
instructions = positionner_texte(instructions, floor(N*SIZE/2 - instructions.surface->w/2), titre.pos.y + 1.5*SIZE);

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

rafraichir(ecran, tete, leserpent, pomme, lepois);
SDL_BlitSurface(titre.surface, NULL, ecran, &(titre.pos));
SDL_BlitSurface(instructions.surface, NULL, ecran, &(instructions.pos));
SDL_Flip(ecran);


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

if (var.partie_finie == 1) {
	

	tableau = charge_scores(feuille_scores, tableau);
	int classement = merite(var.score, tableau);
	if (classement < 11) {
		printf("\nTon score : %d\n", var.score);
		printf("\nta position : %d\n", classement);
		ecrit_score(classement, var.score, feuille_scores, tableau);
	}
	affiche_scores(tableau);
}

printf("\nAu revoir !\n\n");
/******************************************************************/


return 0;
}
