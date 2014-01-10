#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

LISTE_POS creer_liste(void) {
	return NULL;
}

int est_vide(LISTE_POS l) {
	return !l;
}

/*LISTE_POS ajouter_tete(COORDONNEES c, LISTE_POS l) {
	printf("entrée dans ajouter_tete\n");
	LISTE_POS p=creer_liste(); printf("arg\n");
	
	p->coord.abs=c.abs;printf("bla\n");
	p->coord.ord=c.ord;
	
	p->suiv=l;
	return p;
}*/
LISTE_POS ajouter_tete(COORDONNEES c, LISTE_POS l) {
	LISTE_POS p=calloc(1,sizeof(*p));
	if (p==NULL) return NULL;
	p->abs=c.abs;
	p->ord=c.ord;
	p->suiv=l;
	return p;
}

/*LISTE_POS ajouter_queue(COORDONNEES c, LISTE_POS l) {
	printf("entrée dans ajouter_queue\n");
	LISTE_POS p=creer_liste();
	p=l;
	if (!l) {
		printf("gefdcfd\n");
		return ajouter_tete(c,l);
	}
	while (!est_vide(p)) {
		printf("boucle while\n");
		p=p->suiv;
	} //printf("on est arrivé au bout de la liste\n");
	
	//printf("création d'un maillon\n");
	//printf("%d %d\n", c.abs, c.ord);	
	LISTE_POS m;
	m=calloc(1,sizeof(*m));
	if (m==NULL) {
		printf("erreur\n");
		exit(0);
	}	
	//m->coord.abs=41;
	//printf("%d\n", m->coord.abs);
	m->abs=c.abs;
	m->ord=c.ord;
	printf("affichage\n");
	voir_coord(m->coord);

	//on le raccroche à la liste
	p->suiv=m;

	return p;
}*/

LISTE_POS ajouter_queue(COORDONNEES c, LISTE_POS l) {

	//plus malin : return concat(l,c);

	LISTE_POS copie=l;
	if (!l) return ajouter_tete(c,NULL);
	while (l->suiv!=NULL) {
		l=l->suiv;
	}
	l->suiv=ajouter_tete(c,NULL);
	return copie;
}

LISTE_POS supprimer_queue(LISTE_POS l) {
	LISTE_POS p=creer_liste();
	p=l;
	while (!est_vide(p->suiv)) {
		p=p->suiv;
	} //on est à l'avant-dernier de la liste
	
	//suppression de la queue
	free(p->suiv);
	
	p->suiv=NULL;

	return p;
}

void voir_coord(COORDONNEES c) {
	printf("abscisse : %d  ordonnée : %d \n", c.abs, c.ord);
}

void voir_pois(POIS p) {
	printf("abscisse : %d  ordonnée : %d \n", p.abs, p.ord);
}

void voir_liste(LISTE_POS l) {
	LISTE_POS p=creer_liste();
	p=l;
	int i=1;
	while (!est_vide(p)) {
		printf("maillon %d : ", i);
		COORDONNEES c;
		c.abs=p->abs;
		c.ord=p->ord;
		voir_coord(c);
		p=p->suiv;
		i++;
	}
}

void voir_serpent(SERPENT s) {
	COORDONNEES tete;
	tete.abs=s.abs_serp;
	tete.ord=s.ord_serp;	
	voir_coord(tete);
	voir_liste(s.pos_anterieures);
}








