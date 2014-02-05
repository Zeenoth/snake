#include "../include/liste.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>

#include "../include/fonctions.h"



SDL_Surface* creer_fenetre(int largeur, int hauteur) {
	SDL_Surface* fenetre=NULL;

	fenetre = SDL_SetVideoMode(largeur,hauteur, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if( fenetre == NULL ) {
	        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
		exit(0);
    	}   
	SDL_WM_SetCaption("snake",NULL); //pour lui donner un nom

	//printf("coloriage en blanc de la fenêtre graphique\n");
	Uint32 blanc = SDL_MapRGB(fenetre->format, 255, 255, 255);
	SDL_FillRect(fenetre, NULL, blanc);

	SDL_Flip(fenetre);

	return fenetre;
}

void placer_pois(POIS* p, int H, int W) {
	srand(time(NULL));
	int x=rand()%W;
	int y=rand()%H;
	
	p->abscisse=x;
	p->ordonnee=y;
	
	//affiche_case(x,y) pour mettre  le sprite du pois dans la case x,y
}

int cogne_mur(SERPENT s, int H, int W) {
	if (s->coord.abscisse<0 || s->coord.ordonnee<0 || s->coord.abscisse>W-1 || s->coord.ordonnee>H-1) {
		return 1;
	}
	else return 0;
}

int cogne_mur2(SERPENT s, int H, int W) {
	if (s->coord.abscisse < 0) {
		s->coord.abscisse = N-1;
	}

	if (s->coord.abscisse > N-1) {
		s->coord.abscisse = 0;
	}

	if (s->coord.ordonnee < 0) {
		s->coord.ordonnee = N-1;
	}

	if (s->coord.ordonnee > N-1) {
		s->coord.ordonnee = 0;
	}

	return 0;
}

void visualiser_pois(POIS p) {
	printf("coordonnées du pois :\nabscisse %d, ordonnée %d\n", p.abscisse, p.ordonnee);
}

SERPENT grandit(SERPENT s) {
	//printf("entrée dans la fonction grandit\n");
	//création du maillon qui sera la tête
	Maillon tete;
	tete.n = (s->n)+1; //mise à jour de la taille du serpent
	tete.direction = s->direction;

	//pour connaître les coordonnées de la nouvelle tête, il faut savoir dans quelle direction le serpent avance
	switch(s->direction) {
		case droite:
			tete.coord.abscisse = s->coord.abscisse +1;
			tete.coord.ordonnee = s->coord.ordonnee;
			break;
		case gauche:
			tete.coord.abscisse = s->coord.abscisse -1;
			tete.coord.ordonnee = s->coord.ordonnee;
			break;
		case haut:
			tete.coord.abscisse = s->coord.abscisse;
			tete.coord.ordonnee = s->coord.ordonnee -1;
			break;
		case bas:
			tete.coord.abscisse = s->coord.abscisse;
			tete.coord.ordonnee = s->coord.ordonnee +1;
			break;
	}

	s = ajout_tete(tete,s);
	//printf("sortie de la fonction grandit, taille %d\n", s->n);

	return s;
}

void affiche_serpent(SDL_Surface* ecran, SDL_Surface* sprite, SERPENT s) {
	//il s'agit de parcourir le serpent et d'afficher chaque segment de son corps

	Liste p = s;
	
	SDL_Surface* tete = NULL;
	SDL_Rect position_segment;
	position_segment.x = (p->coord.abscisse) * SIZE;
	position_segment.y = (p->coord.ordonnee) * SIZE;

	switch(s->direction) {
		case droite: 
			tete = IMG_Load("data/droite.png");
			SDL_BlitSurface(tete, NULL, ecran, &position_segment);
			break;

		case gauche: 
			tete = IMG_Load("data/gauche.png");
			SDL_BlitSurface(tete, NULL, ecran, &position_segment);
			break;

		case bas: 
			tete = IMG_Load("data/bas.png");
			SDL_BlitSurface(tete, NULL, ecran, &position_segment);
			break;

		case haut: 
			tete = IMG_Load("data/haut.png");
			SDL_BlitSurface(tete, NULL, ecran, &position_segment);
			break;
	}

	p = p->suiv;	

	while (est_vide(p)==0) {
		SDL_Rect position_segment;
		position_segment.x = (p->coord.abscisse) * SIZE;
		position_segment.y = (p->coord.ordonnee) * SIZE;
		SDL_BlitSurface(sprite, NULL, ecran, &position_segment);
		p=p->suiv;
	}
	
	SDL_Flip(ecran);
}

void affiche_pois(SDL_Surface* ecran, SDL_Surface* sprite, POIS p) {

        SDL_Rect position;
        position.x = (p.abscisse) * SIZE;
        position.y = (p.ordonnee) * SIZE;
        SDL_BlitSurface(sprite, NULL, ecran, &position);
        
        SDL_Flip(ecran);
}

int mange_pois(SERPENT s, POIS p) {
	//printf("\nentrée dans la fonction mange pois\n");

	if (s->coord.abscisse == p.abscisse && s->coord.ordonnee == p.ordonnee) {
		//printf("mange pois = 1\n");
		return 1;
	}

	//printf("mange pois = 0\n");
	return 0;
}

int mange_serpent(SERPENT s) {
	
	Liste p = s->suiv;

	while (est_vide(p) == 0) {
		if (p->coord.abscisse == s->coord.abscisse && p->coord.ordonnee == s->coord.ordonnee) {
			return 1;
		}
		p = p->suiv;
	}

	return 0;
}

SERPENT avance(SERPENT s) {	
	//la tête va avancer d'une case dans la direction
	//chaque segment va prendre les coordonnées de celui qui le précède

	Liste cop = copie(s);
	//printf("\n la liste copiée est :\n");
	//visualiser_liste(cop);

	//pour connaître les coordonnées de la nouvelle tête, il faut savoir dans quelle direction le serpent avance
	switch(s->direction) {
		case droite:
			s->coord.abscisse = s->coord.abscisse +1;
			s->coord.ordonnee = s->coord.ordonnee;
			break;
		case gauche:
			s->coord.abscisse = s->coord.abscisse -1;
			s->coord.ordonnee = s->coord.ordonnee;
			break;
		case haut:
			s->coord.abscisse = s->coord.abscisse;
			s->coord.ordonnee = s->coord.ordonnee -1;
			break;
		case bas:
			s->coord.abscisse = s->coord.abscisse;
			s->coord.ordonnee = s->coord.ordonnee +1;
			break;
	}

	//printf("\nla tete a avancé mais le corps pas encore");
	//visualiser_liste(s);

	Liste p = s->suiv;
	Liste c = cop;

	while (est_vide(p) == 0) {
		p->coord.abscisse = c->coord.abscisse;
		p->coord.ordonnee = c->coord.ordonnee;

		p = p->suiv;
		c = c->suiv;
	}

	return s;
}

void rafraichir(SDL_Surface* ecran, SDL_Surface* tete, SERPENT s, SDL_Surface* pomme, POIS p, TEXTE* lescore, int score_num) {
	//On efface l'écran (ici fond blanc) :
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	//Mise à jour du score à afficher
	char score_courant[30];
	snprintf(score_courant, 30, "Score : %d", score_num);
	SDL_Color noir = {0, 0, 0};
	*lescore = creer_texte(*lescore, "data/moonflowerbold.ttf", 34, score_courant, noir);
	*lescore = positionner_texte(*lescore, floor(N*SIZE - lescore->surface->w), 0);
     
	/* On fait tous les SDL_BlitSurface nécessaires pour coller les surfaces à l'écran */
	affiche_pois(ecran, pomme, p);
	affiche_serpent(ecran, tete, s);
	SDL_BlitSurface(lescore->surface, NULL, ecran, &(lescore->pos));
 
	/* On met à jour l'affichage : */
	SDL_Flip(ecran);
}

TEXTE creer_texte(TEXTE montexte,char* mapolice, int taille, char* message, SDL_Color couleur) {
	//printf("entrée dans creer_texte\n");
	montexte.font = TTF_OpenFont(mapolice, taille);
	if (montexte.font == NULL) {
		printf("%s\n", TTF_GetError());
		//exit(0);
	}
	
	montexte.color = couleur;
	montexte.surface = TTF_RenderText_Blended(montexte.font, message, montexte.color);
	
	return montexte;
}

TEXTE positionner_texte(TEXTE montexte, int x, int y) {
	
	montexte.pos.x = x;
	montexte.pos.y = y;

	return montexte;
}

void affiche_scores(SDL_Surface* ecran, SCORE* t, char* police, SDL_Color couleur) {
	printf("entrée dans affiche_scores\n");

	TEXTE palmares;
	palmares = creer_texte(palmares, police, 47, "Palmares :", couleur);
	palmares = positionner_texte(palmares, floor(N*SIZE/2) - palmares.surface->w/2, floor(N*SIZE/8));
	SDL_BlitSurface(palmares.surface, NULL, ecran, &(palmares.pos));

	TEXTE tableau[10];	//tableau des dix scores à afficher (posision, joueur et points)
	char numero[30];	//texte à mettre dans les TEXTE

	int i = 0;
	for (i = 0 ; i < 10 ; i++) {
		snprintf(numero, 30, "%.2d %s : %d", i+1, t[i].player, t[i].resultat);
		tableau[i] = creer_texte(tableau[i], police, 30, numero, couleur);
		tableau[i] = positionner_texte(tableau[i], floor(N*SIZE/2) - tableau[i].surface->w/2, floor(N*SIZE*(i*0.4)/8 + N*SIZE*0.7/8 + 2*palmares.surface->h));
		SDL_BlitSurface(tableau[i].surface, NULL, ecran, &(tableau[i].pos));
	}

	SDL_Flip(ecran);

}








	
