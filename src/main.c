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

SIZE = 70;
N = 10;
UT = 450;
int nouvelle_partie = 1;
SDL_Color noir = {0, 0, 0};
SDL_Color rose = {193, 106, 106};

//on décide d'ignorer les mouvements de souris et les relâchements de touches du clavier
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);	

/******************************************************************/
		//INITIALISATION DE LA SDL ET CRÉATION DE LA FENÊTRE

SDL_Surface* ecran = NULL;
int taille_fenetre = SIZE*N; //taille de la fenêtre en pixels
ecran = init_SDL(ecran, taille_fenetre);

/******************************************************************/

/*C'est ici qu'on propose les différents modes de jeu :
 * normal
 * avec les bords de l'écran
 * multijoueur...
 * il faut afficher les différents choix
 * considérer les zones de texte comme des boutons pour que le joueur clique dessus
 * il faudrait aussi qu'on puisse les sélectionner grâce au clavier : l'option sélectionnée apparaîtrait plus gros
 * */

TEXTE titre;
titre = creer_texte(titre, "data/alphawood.ttf", 75, "Bienvenue dans Snake", noir);
titre = positionner_texte(titre, floor(N*SIZE/2 - titre.surface->w/2), floor(N*SIZE/6));

TEXTE modeLibre;
modeLibre = creer_texte(modeLibre, "data/alphawood.ttf", 60, "Mode sans bords", rose);
modeLibre = positionner_texte(modeLibre, floor(N*SIZE/2 - modeLibre.surface->w/2), floor(N*SIZE/4) + 1.3*titre.surface->h);

TEXTE modeNormal;
modeNormal = creer_texte(modeNormal, "data/alphawood.ttf", 60, "Mode normal", noir);
modeNormal = positionner_texte(modeNormal, floor(N*SIZE/2 - modeNormal.surface->w/2), modeLibre.pos.y + 1.3*modeLibre.surface->h);

TEXTE modeMulti;
modeMulti = creer_texte(modeMulti, "data/alphawood.ttf", 60, "Mode multijoueur", noir);
modeMulti = positionner_texte(modeMulti, floor(N*SIZE/2 - modeMulti.surface->w/2), modeNormal.pos.y + 1.3*modeNormal.surface->h);

TEXTE modeAutre;
modeAutre = creer_texte(modeAutre, "data/alphawood.ttf", 60, "autre mode", noir);
modeAutre = positionner_texte(modeAutre, floor(N*SIZE/2 - modeAutre.surface->w/2), modeMulti.pos.y + 1.3*modeMulti.surface->h);

SDL_BlitSurface(titre.surface, NULL, ecran, &(titre.pos));
SDL_BlitSurface(modeLibre.surface, NULL, ecran, &(modeLibre.pos));
SDL_BlitSurface(modeNormal.surface, NULL, ecran, &(modeNormal.pos));
SDL_BlitSurface(modeMulti.surface, NULL, ecran, &(modeMulti.pos));
SDL_BlitSurface(modeAutre.surface, NULL, ecran, &(modeAutre.pos));

SDL_Flip(ecran);

//choix :
int jaichoisi = 0;
int lechoix = 1; //par défaut c'est le mode sans bords qui est sélectionné
/*Si le joueur appuie sur haut, choix--
 * si choix<1 alors choix=dernière possibilité
 * la fonction renvoie le numéro du choix dès que le joueur appuie sur haut ou bas
 * il faut alors actualiser l'affichage pour que le choix apparaisse en couleur
 * si on a validé son choix, jaichoisi va prendre la valeur 1 et on lance le programme principal
 * */
while (jaichoisi == 0) {
	lechoix = clique_menu(&jaichoisi, lechoix);
	printf("choix : %d\n", lechoix);
	if (lechoix == -14) {
		goto quitter_programme;
	}
}
SDL_Delay(1000);

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


/*******************************************************************/
		//CRÉATION DU SERPENT

//taille initiale du serpent
int taille_serpent = 3;

SERPENT leserpent = calloc(1, sizeof(*leserpent));
leserpent = init_serpent(leserpent, taille_serpent);
//visualiser_liste(leserpent);

/******************************************************************/
		//PLACEMENT DU POIS

srand(time(NULL)); //initialisation de la fonction random
POIS lepois;
lepois = init_pois(lepois, leserpent);
//visualiser_pois(lepois);

/*******************************************************************/
//chargement des sprites
SDL_Surface* pomme = NULL;
pomme = IMG_Load("data/apple60.png");

SDL_Surface* tete = NULL;
tete = IMG_Load("data/corps.png");

//chargement des textes à afficher

TEXTE instructions;
instructions = creer_texte(instructions, "data/alphawood.ttf", 35, "Appuie sur une touche pour commencer", noir);
instructions = positionner_texte(instructions, floor(N*SIZE/2 - instructions.surface->w/2), titre.pos.y + 1.5*SIZE);

TEXTE info;
info = creer_texte(info, "data/alphawood.ttf", 35, "Appuie sur P pour mettre en pause", noir);
info = positionner_texte(info, N*SIZE/2 - info.surface->w/2, N*SIZE*4/5);

TEXTE lescore;
char score_courant[30];
snprintf(score_courant, 30, "Score : %d", var.score);
lescore = creer_texte(lescore, "data/moonflowerbold.ttf", 24, score_courant, noir);
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
	TEXTE resultat;
	char score_final[30];
	snprintf(score_final, 30, "Ton score : %d", var.score);
	resultat = creer_texte(resultat, "data/moonflowerbold.ttf", 35, score_final, noir);
	resultat = positionner_texte(resultat, floor(N*SIZE/2 - resultat.surface->w/2), 20);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	SDL_BlitSurface(resultat.surface, NULL, ecran, &(resultat.pos));
	SDL_Flip(ecran);

	tableau = charge_scores(feuille_scores, tableau);
	int classement = merite(var.score, tableau);
	if (classement < 11) {
		//printf("\nTon score : %d\n", var.score);
		//printf("\nta position : %d\n", classement);
		ecrit_score(classement, var.score, feuille_scores, tableau);
	}
	//visualiser_scores(tableau);
	tableau  = charge_scores(feuille_scores, tableau);
	affiche_scores(ecran, tableau, "data/moonflowerbold.ttf", noir);
	/*on veut afficher un bouton "OK" à la fin des scores pour continuer
	* on peut aussi appuyer sur entrée au clavier
	* */
	BOUTONS boutonok;
	boutonok = placer1bouton(ecran, boutonok);
//	SDL_Delay(4000);
	while (clique_ok(boutonok) != 0 && clique_ok(boutonok) != -14) {
	}
}



/********************************************************************/

/*ici, on veut afficher le texte "veux-tu recommencer une partie ?"
 * puis deux boutons, oui et non, sur lesquels on peut cliquer pour choisir
 * on peut aussi appuyer sur o et n du clavier
 * */
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

//affichage de la question et du score final
TEXTE final;
TEXTE question1;
TEXTE question2;
question1 = creer_texte(question1, "data/alphawood.ttf", 50, "Veux tu refaire", noir);
question2 = creer_texte(question2, "data/alphawood.ttf", 50, "une partie ?", noir);
char score_final[30];
snprintf(score_final, 30, "Ton score : %d", var.score);
final = creer_texte(final, "data/moonflowerbold.ttf", 50, score_final, noir);
question1 = positionner_texte(question1, floor(N*SIZE/2 - question1.surface->w/2), floor(N*SIZE/4));
question2 = positionner_texte(question2, floor(N*SIZE/2 - question2.surface->w/2), floor(N*SIZE/4) + 50);
final = positionner_texte(final, floor(N*SIZE/2) - final.surface->w/2, floor(N*SIZE/8));
SDL_BlitSurface(question1.surface, NULL, ecran, &(question1.pos));
SDL_BlitSurface(question2.surface, NULL, ecran, &(question2.pos));
SDL_BlitSurface(final.surface, NULL, ecran, &(final.pos));

//affichage des boutons
BOUTONS lesboutons;
lesboutons = placer_boutons(ecran, lesboutons);

if (clique_recommence(lesboutons) == 1) {
	nouvelle_partie = 1;
}
else {
	nouvelle_partie = 0;
}

} //fin du while(nouvelle partie)

quitter_programme:
printf("\nAu revoir!\n\n");

//faire tous les free() nécessaires : polices, surfaces, etc

return 0;
}
