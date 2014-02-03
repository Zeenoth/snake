#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

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

#ifndef _TEXTE_
#define _TEXTE_

//Structure utile pour l'affichage du texte
typedef struct {
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Rect pos;	//la position
} TEXTE;
#endif

//ouverture d'une fenêtre graphique blanche
SDL_Surface* creer_fenetre(int largeur, int hauteur);

//fonction qui place un pois (l'affichage n'est pas encore pris en compte ; à la fin la fonction retournera void)
void placer_pois(POIS* p, int H, int W);

//fonction qui teste si le serpent s'est pris un mur. Retourne 1 si le serpent s'est cogné et 0 sinon
int cogne_mur(SERPENT s, int H, int W);

//fonction qui fait traverser les murs : le serpent réapparaît de l'autre côté de l'écran
int cogne_mur2(SERPENT s, int H, int W);

//affiche les coordonnées du pois
void visualiser_pois(POIS p);

//fonction qui fait grandir le serpent. Elle ajoute un maillon en tête suivant la direction dans laquelle avance le serpent et fait n++
SERPENT grandit(SERPENT s);

//affiche le serpent dans la fenêtre graphique
void affiche_serpent(SDL_Surface* ecran, SDL_Surface* sprite, SERPENT s);

//affiche le pois dans la fenêtre graphique
void affiche_pois(SDL_Surface* ecran, SDL_Surface* sprite, POIS p);

//vérifie si la tête du serpent est sur la case du pois : renvoie 1 si le pois est atteint, 0 sinon
int mange_pois(SERPENT s, POIS p);

//vérifie si le serpent se mange tout seul : renvoie 1 si oui et 0 sinon
int mange_serpent(SERPENT s);

//fait avancer le serpent d'une position (met à jour les coordonnées)
SERPENT avance(SERPENT s);

//met à jour l'affichage : vide l'écran et affiche les nouvelles positions du pois et du serpent
void rafraichir(SDL_Surface* ecran, SDL_Surface* tete, SERPENT s, SDL_Surface* pomme, POIS p, TEXTE* lescore, int score_num);

//fonctions qui remplissent une structure TEXTE afin qu'il n'y ait plus qu'à la blitter.
//Attention, il faut les appeler dans cet ordre si on veut que la position du texte dépende de sa taille (centré dans la fenêtre par ex)
//x et y sont l'abscisse et l'ordonnée du coin supérieur gauche de l'étiquette contenant le texte.
TEXTE creer_texte(TEXTE montexte,char* mapolice, int taille, char* message, SDL_Color couleur);
TEXTE positionner_texte(TEXTE montexte, int x, int y);

#endif
