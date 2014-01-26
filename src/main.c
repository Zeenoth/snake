#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "../include/liste.h"
#include "../include/fonctions.h"
#include "../include/init.h"
#include "../include/global.h"
#include "../include/controle.h"
#include "../include/fichier.h"


int main(int argc, char* argv[]) {

int nouvelle_partie = 1;

while (nouvelle_partie) { //on peut choisir de recommencer quand on a perdu

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


/*******************************************************************/
//chargement des sprites
SDL_Surface* pomme = NULL;
pomme = IMG_Load("sprites/apple60.png");

SDL_Surface* tete = NULL;
tete = IMG_Load("sprites/corps.png");

//chargement des textes à afficher
SDL_Color noir = {0, 0, 0};

TEXTE titre;
titre = creer_texte(titre, "sprites/alphawood.ttf", 75, "Bienvenue dans Snake", noir);
titre = positionner_texte(titre, floor(N*SIZE/2 - titre.surface->w/2), floor(N*SIZE/4));

TEXTE instructions;
instructions = creer_texte(instructions, "sprites/alphawood.ttf", 35, "Appuie sur une touche pour commencer", noir);
instructions = positionner_texte(instructions, floor(N*SIZE/2 - instructions.surface->w/2), titre.pos.y + 1.5*SIZE);

TEXTE lescore;
char score_courant[30];
snprintf(score_courant, 30, "Score : %d", var.score);
lescore = creer_texte(lescore, "sprites/Fibography_PersonalUse.ttf", 24, score_courant, noir);
lescore = positionner_texte(lescore, floor(N*SIZE - lescore.surface->w), 0);

//on décide d'ignorer les mouvements de souris et les relâchements de touches du clavier
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);	

printf("\nFIN DE L'INITIALISATION\n\n");

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

rafraichir(ecran, tete, leserpent, pomme, lepois, &lescore, var.score);
SDL_BlitSurface(titre.surface, NULL, ecran, &(titre.pos));
SDL_BlitSurface(instructions.surface, NULL, ecran, &(instructions.pos));
SDL_BlitSurface(lescore.surface, NULL, ecran, &(lescore.pos));
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

var = controle(ecran, leserpent, lepois, tete, pomme, var, lescore);

if (var.partie_finie == 1) {
	//affichage du score final
	TEXTE resultat;
	char score_final[30];
	snprintf(score_final, 30, "Ton score : %d", var.score);
	resultat = creer_texte(resultat, "sprites/Fibography_PersonalUse.ttf", 35, score_final, noir);
	resultat = positionner_texte(resultat, floor(N*SIZE/2 - resultat.surface->w/2), 0);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	SDL_BlitSurface(resultat.surface, NULL, ecran, &(resultat.pos));
	SDL_Flip(ecran);

	tableau = charge_scores(feuille_scores, tableau);
	int classement = merite(var.score, tableau);
	if (classement < 11) {
		printf("\nTon score : %d\n", var.score);
		printf("\nta position : %d\n", classement);
		ecrit_score(classement, var.score, feuille_scores, tableau);
	}
	affiche_scores(tableau);
}
// À PARTIR DE LÀ ÇA A CHANGÉ
/*ici, on veut afficher le texte "veux-tu recommencer une partie ?"
 * puis deux boutons, oui et non, sur lesquels on peut cliquer pour choisir
 * */
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
 
TEXTE question1; //la question ne rentre pas sur une ligne
TEXTE question2;
//TEXTE question3;
question1 = creer_texte(question1, "sprites/alphawood.ttf", 50, "Veux tu recommencer", noir);
question2 = creer_texte(question2, "sprites/alphawood.ttf", 50, "une partie ?", noir);
question1 = positionner_texte(question1, floor(N*SIZE/2 - question1.surface->w/2), floor(N*SIZE/4));
question2 = positionner_texte(question2, floor(N*SIZE/2 - question2.surface->w/2), floor(N*SIZE/4) + 50);
SDL_BlitSurface(question1.surface, NULL, ecran, &(question1.pos));
SDL_BlitSurface(question2.surface, NULL, ecran, &(question2.pos));
SDL_Flip(ecran);

/******************************************************************/
printf("\nVeux-tu recommencer une partie ? [o/n]\n\n");
	char recommencer;
	scanf("%s", &recommencer);
	if (recommencer == 'o') {
		printf("coucou\n");
	}
	else {
		printf("\n\nAu revoir!\n");
		nouvelle_partie = 0;
	}
	
/******************************************************************/
} //fin du while(nouvelle partie)

return 0;
}
