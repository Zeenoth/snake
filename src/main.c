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
#include "../include/graphique.h"


int main(int argc, char* argv[]) {

	//on décide d'ignorer les mouvements de souris et les relâchements de touches du clavier
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);

int nouvelle_partie = 1;
VARIABLES var;
SDL_Color noir = {0, 0, 0};
SDL_Color rose = {193, 106, 106};
FILE* feuille_scores = NULL;
SCORE* tableau = NULL;
SDL_Surface* ecran = NULL;
int taille_fenetre;
TEXTE modes[5];	//tableau des zones de textes des modes de jeu
TEXTE curseur;
int lechoix = 1;	//par défaut c'est le mode sans bords qui est sélectionné
int taille_serpent;
SERPENT leserpent;
srand(time(NULL)); //initialisation de la fonction random
POIS lepois;
SDL_Surface* pomme = NULL;
SDL_Surface* tete = NULL;
TEXTE titre;
TEXTE instructions;
TEXTE info;
TEXTE lescore;
char score_courant[30];
TEXTE resultat;
char score_final[30];
int classement;
TEXTE question1;
TEXTE question2;
BOUTONS boutonok; //bouton pour quitter l'affichage des meilleurs scores
BOUTONS lesboutons; //bouton pour choisir de recommencer une partie


while (nouvelle_partie) { //on peut choisir de recommencer quand on a perdu

	

/******************************************************************/
		//VARIABLES UTILES POUR LE PROGRAMME


var.partie_finie = 0; //vaut 0 tant que le joueur n'a pas perdu ni quitté le jeu, 1 sinon
var.score = 0; //compte le nombre de pois mangés par le serpent
var.continuer = 1;
var.mange = 0; //s"il mange le pois
var.flag = 0;
var.cogne = 0; //s'il se cogne contre un mur
var.queue = 0; //s'il se mord la queue
//var.mode est initialisé quand le joueur choisit le mode de jeu


tableau = init_scores(); //alloue et initialise le tableau des scores
SIZE = 70;
N = 10;
UT = 450;

/*******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE

taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);

/******************************************************************/
		//CHOIX DU MODE DE JEU

/*C'est ici qu'on propose les différents modes de jeu :
 * normal
 * avec les bords de l'écran
 * multijoueur...
 * il faut afficher les différents choix
 * considérer les zones de texte comme des boutons pour que le joueur clique dessus
 * il faudrait aussi qu'on puisse les sélectionner grâce au clavier : l'option sélectionnée apparaîtrait plus gros
 * */



//titre
modes[0] = creer_texte(modes[0], "data/alphawood.ttf", 75, "Bienvenue dans Snake", noir);
modes[0] = positionner_texte(modes[0], floor(N*SIZE/2 - modes[0].surface->w/2), floor(N*SIZE/6));

//mode sans bords
modes[1] = creer_texte(modes[1], "data/alphawood.ttf", 60, "Mode sans bords", noir);
modes[1] = positionner_texte(modes[1], floor(N*SIZE/2 - modes[1].surface->w/2), floor(N*SIZE/4) + 1.3*modes[0].surface->h);

//mode avec les bords de l'écran
modes[2] = creer_texte(modes[2], "data/alphawood.ttf", 60, "Mode normal", noir);
modes[2] = positionner_texte(modes[2], floor(N*SIZE/2 - modes[2].surface->w/2), modes[1].pos.y + 1.3*modes[1].surface->h);

//mode de jeu à deux joueurs
modes[3] = creer_texte(modes[3], "data/alphawood.ttf", 60, "Mode multijoueur", noir);
modes[3] = positionner_texte(modes[3], floor(N*SIZE/2 - modes[3].surface->w/2), modes[2].pos.y + 1.3*modes[2].surface->h);

//possibilité d'inventer un autre mode de jeu
modes[4] = creer_texte(modes[4], "data/alphawood.ttf", 60, "autre mode", noir);
modes[4] = positionner_texte(modes[4], floor(N*SIZE/2 - modes[4].surface->w/2), modes[3].pos.y + 1.3*modes[3].surface->h);

//curseur montrant le choix sélectionné
curseur = creer_texte(curseur, "data/ubuntu.ttf", 60, "=>", rose);
curseur = positionner_texte(curseur, floor(modes[1].pos.x - curseur.surface->w), floor(modes[1].pos.y));

SDL_BlitSurface(modes[0].surface, NULL, ecran, &(modes[0].pos));
SDL_BlitSurface(modes[1].surface, NULL, ecran, &(modes[1].pos));
SDL_BlitSurface(modes[2].surface, NULL, ecran, &(modes[2].pos));
SDL_BlitSurface(modes[3].surface, NULL, ecran, &(modes[3].pos));
SDL_BlitSurface(modes[4].surface, NULL, ecran, &(modes[4].pos));
SDL_BlitSurface(curseur.surface, NULL, ecran, &(curseur.pos));

SDL_Flip(ecran);



lechoix = choisir_mode(lechoix, ecran, curseur, modes);
if (lechoix == -14) {
	goto quitter_programme;
}
var.mode = lechoix;
printf("c'est choisi ! : mode %d\n", var.mode);

/******************************************************************/
		//CRÉATION DU SERPENT

//taille initiale du serpent
taille_serpent = 3;

leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent);
//visualiser_liste(leserpent);

/******************************************************************/
		//PLACEMENT DU POIS

lepois = init_pois(lepois, leserpent);
//visualiser_pois(lepois);

/*******************************************************************/
		//CHARGEMENT DES SPRITES

pomme = IMG_Load("data/apple60.png");

tete = IMG_Load("data/corps.png");

//chargement des textes à afficher

titre = creer_texte(titre, "data/alphawood.ttf", 75, "Bienvenue dans Snake", noir);
titre = positionner_texte(titre, floor(N*SIZE/2 - titre.surface->w/2), floor(N*SIZE/4));

instructions = creer_texte(instructions, "data/alphawood.ttf", 35, "Appuie sur une touche pour commencer", noir);
instructions = positionner_texte(instructions, floor(N*SIZE/2 - instructions.surface->w/2), titre.pos.y + 1.5*SIZE);

info = creer_texte(info, "data/alphawood.ttf", 35, "Appuie sur P pour mettre en pause", noir);
info = positionner_texte(info, N*SIZE/2 - info.surface->w/2, N*SIZE*4/5);

snprintf(score_courant, 30, "Score : %d", var.score);
lescore = creer_texte(lescore, "data/Fibography_PersonalUse.ttf", 24, score_courant, noir);
lescore = positionner_texte(lescore, floor(N*SIZE - lescore.surface->w), 0);

printf("\nFIN DE L'INITIALISATION\n\n");

/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

rafraichir(ecran, tete, leserpent, pomme, lepois, &lescore, var.score);
SDL_BlitSurface(titre.surface, NULL, ecran, &(titre.pos));
SDL_BlitSurface(instructions.surface, NULL, ecran, &(instructions.pos));
SDL_BlitSurface(lescore.surface, NULL, ecran, &(lescore.pos));
SDL_BlitSurface(info.surface, NULL, ecran, &(info.pos));
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
 * 	demander si le joueur veut refaire une partie
 */

var = controle(ecran, leserpent, lepois, tete, pomme, var, lescore);

if (var.partie_finie == 1) {
	//affichage du score final
	snprintf(score_final, 30, "Ton score : %d", var.score);
	resultat = creer_texte(resultat, "data/moonflowerbold.ttf", 35, score_final, noir);
	resultat = positionner_texte(resultat, floor(N*SIZE/2 - resultat.surface->w/2), 20);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	SDL_BlitSurface(resultat.surface, NULL, ecran, &(resultat.pos));
	
	SDL_Flip(ecran);

	tableau = charge_scores(feuille_scores, tableau);
	classement = merite(var.score, tableau);
	if (classement < 11) {
		printf("\nTon score : %d\n", var.score);
		printf("\nta position : %d\n", classement);
		ecrit_score(classement, var.score, feuille_scores, tableau);
	}
	visualiser_scores(tableau);
	tableau = charge_scores(feuille_scores, tableau);
	affiche_scores(ecran, tableau, "data/moonflowerbold.ttf", noir);
	
	//bouton OK pour dire qu'on a fini de regarder les scores
	boutonok = placer1bouton(ecran, boutonok);
	while (clique_ok(boutonok) != 0 && clique_ok(boutonok) != -14) {
	}
}

/********************************************************************/

/*ici, on veut afficher le texte "veux-tu recommencer une partie ?"
 * puis deux boutons, oui et non, sur lesquels on peut cliquer pour choisir
 * */
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

//affichage de la question 
question1 = creer_texte(question1, "data/alphawood.ttf", 50, "Veux tu recommencer", noir);
question2 = creer_texte(question2, "data/alphawood.ttf", 50, "une partie ?", noir);
snprintf(score_final, 30, "Ton score : %d", var.score);
question1 = positionner_texte(question1, floor(N*SIZE/2 - question1.surface->w/2), floor(N*SIZE/4));
question2 = positionner_texte(question2, floor(N*SIZE/2 - question2.surface->w/2), floor(N*SIZE/4) + 50);
SDL_BlitSurface(question1.surface, NULL, ecran, &(question1.pos));
SDL_BlitSurface(question2.surface, NULL, ecran, &(question2.pos));
SDL_BlitSurface(resultat.surface, NULL, ecran, &(resultat.pos));

//affichage des boutons
lesboutons = placer_boutons(ecran, lesboutons);

if (clique_recommence(lesboutons) == 1) {
	nouvelle_partie = 1;
}
else {
	nouvelle_partie = 0;
}

} //fin du while(nouvelle partie)

printf("quitter programme\n");
quitter_programme:
printf("\n\nAu revoir!\n");

return 0;
}
