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
		//VARIABLES UTILES POUR LE PROGRAMME

UT = 450;
VARIABLES var;
var.partie_finie = 0; //vaut 0 tant que le joueur n'a pas perdu ni quitté le jeu, 1 sinon
var.score = 0; //compte le nombre de pois mangés par le serpent
var.continuer = 1;
var.mange = 0; //s"il mange le pois
var.flag = 0;
var.cogne = 0; //s'il se cogne contre un mur
var.queue = 0; //s'il se mord la queue
//var.mode sera initialisé quand le joueur aura choisi le mode de jeu
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
TEXTE modes[5];	//tableau des zones de textes des modes de jeu

TEXTE instructions;
instructions = creer_texte(instructions, "data/alphawood.ttf", 35, "Appuie sur une touche pour commencer", noir);
instructions = positionner_texte(instructions, floor(N*SIZE/2 - instructions.surface->w/2), modes[0].pos.y + 1.5*SIZE);

TEXTE info;
info = creer_texte(info, "data/alphawood.ttf", 35, "Appuie sur P pour mettre en pause", noir);
info = positionner_texte(info, N*SIZE/2 - info.surface->w/2, N*SIZE*4/5);

TEXTE lescore;
char score_courant[30];
snprintf(score_courant, 30, "Score : %d", var.score);
char* police_score = NULL;
police_score = "/home/sophie/Bureau/snake/data/moonflowerbold.ttf";
lescore = creer_texte(lescore, police_score, 24, score_courant, noir);
lescore = positionner_texte(lescore, floor(N*SIZE - lescore.surface->w), 0);

//deux variables pour afficher le score final à la fin de la partie
TEXTE resultat;
resultat.font = NULL;
char score_final[30];
TEXTE question1;
question1.font = NULL;
TEXTE question2;
question2.font = NULL;

BOUTONS boutonok; //bouton pour quitter l'affichage des meilleurs scores
	boutonok.bouton1 = NULL;
	boutonok.bouton2 = NULL;
	boutonok.bouton3 = NULL;
BOUTONS lesboutons; //boutons pour choisir de recommencer une partie
	lesboutons.bouton1 = NULL;
	lesboutons.bouton2 = NULL;
	lesboutons.bouton3 = NULL;

printf("\nFIN DE L'INITIALISATION\n\n");


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
TEXTE curseur;
curseur = creer_texte(curseur, "data/ubuntu.ttf", 60, "=>", rose);
curseur = positionner_texte(curseur, floor(modes[1].pos.x - curseur.surface->w), floor(modes[1].pos.y));

/*Début du jeu à proprement parler*/
while (nouvelle_partie) { //on peut choisir de recommencer quand on a perdu
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


SDL_BlitSurface(modes[0].surface, NULL, ecran, &(modes[0].pos));
SDL_BlitSurface(modes[1].surface, NULL, ecran, &(modes[1].pos));
SDL_BlitSurface(modes[2].surface, NULL, ecran, &(modes[2].pos));
SDL_BlitSurface(modes[3].surface, NULL, ecran, &(modes[3].pos));
SDL_BlitSurface(modes[4].surface, NULL, ecran, &(modes[4].pos));
SDL_BlitSurface(curseur.surface, NULL, ecran, &(curseur.pos));

SDL_Flip(ecran);

//choix :
int lechoix = 1;	//par défaut c'est le mode sans bords qui est sélectionné

/*Si le joueur appuie sur haut, choix--
 * si choix<1 alors choix=dernière possibilité
 * la fonction renvoie le numéro du choix dès que le joueur appuie sur haut ou bas
 * il faut alors actualiser l'affichage pour que le choix apparaisse en couleur
 * si on a validé son choix, jaichoisi va prendre la valeur 1 et on lance le programme principal
 * */
lechoix = choisir_mode(lechoix, ecran, curseur, modes);
if (lechoix == -14) {
	goto quitter_programme;
}
printf("c'est choisi !\n");
var.mode = lechoix;




/******************************************************************/
		//BOUCLE DU PROGRAMME PRINCIPAL

rafraichir(ecran, tete, leserpent, pomme, lepois, &lescore, var.score);
SDL_BlitSurface(modes[0].surface, NULL, ecran, &(modes[0].pos));
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
	
	boutonok = placer1bouton(ecran, boutonok);
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

question1 = creer_texte(question1, "data/alphawood.ttf", 50, "Veux tu refaire", noir);
question2 = creer_texte(question2, "data/alphawood.ttf", 50, "une partie ?", noir);
snprintf(score_final, 30, "Ton score : %d", var.score);
//final = creer_texte(final, "data/moonflowerbold.ttf", 50, score_final, noir);
question1 = positionner_texte(question1, floor(N*SIZE/2 - question1.surface->w/2), floor(N*SIZE/4));
question2 = positionner_texte(question2, floor(N*SIZE/2 - question2.surface->w/2), floor(N*SIZE/4) + 50);
//final = positionner_texte(final, floor(N*SIZE/2) - final.surface->w/2, floor(N*SIZE/8));
SDL_BlitSurface(question1.surface, NULL, ecran, &(question1.pos));
SDL_BlitSurface(question2.surface, NULL, ecran, &(question2.pos));
SDL_BlitSurface(resultat.surface, NULL, ecran, &(resultat.pos));


//affichage des boutons
lesboutons = placer_boutons(ecran, lesboutons);

if (clique_recommence(lesboutons) == 1) {
	nouvelle_partie = 1;
}
else {	nouvelle_partie = 0;}

} //fin du while(nouvelle partie)

quitter_programme:
printf("\nAu revoir!\n\n");

//faire tous les free() nécessaires : polices, surfaces, etc
/*TEXTE
curseur
instructions
info
lescore
resultat
modes[5]
final
question1
question2

char* police_score
char score_courant[30]
char score_final[30]

SDL_Surface* ecran
SDL_Surface* pomme
SDL_Surface* tete

FILE* feuille_scores
SCORE* tableau

SERPENT leserpent
BOUTONS boutonok
BOUTONS lesboutons*/

TTF_CloseFont(curseur.font);
TTF_CloseFont(instructions.font);
TTF_CloseFont(info.font);
TTF_CloseFont(lescore.font);
//ici la segfault
if (resultat.font != NULL) {
	TTF_CloseFont(resultat.font);
	TTF_CloseFont(question1.font);
	TTF_CloseFont(question2.font);
}

int i;
for (i=0 ; i<5 ; i++) {
	TTF_CloseFont(modes[i].font);
}
TTF_Quit();

SDL_FreeSurface(ecran);
SDL_FreeSurface(pomme);
SDL_FreeSurface(tete);
SDL_FreeSurface(boutonok.bouton1);
if (lesboutons.bouton1 != NULL) {
	SDL_FreeSurface(lesboutons.bouton1);
}
if (lesboutons.bouton2 != NULL) {
	SDL_FreeSurface(lesboutons.bouton2);
}


//leserpent = supprime_tout(leserpent);



return 0;
}
