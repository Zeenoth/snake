#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "liste.h"
#include "fonctions.h"
#include "init.h"

Liste creer_liste(void) {
	return NULL;
}

int est_vide(Liste l) {
		if (l==NULL) {
			return 1;
		}
		else return 0;
}

int visualiser_liste(Liste l) {
	//printf("entrée dans visualiser liste\n");

	if (est_vide(l) == 1) {
		printf("liste vide\n");
		return 2;
	}

	printf("taille du serpent %d\n", l->n);
	printf("direction : %d\n", l->direction);
	
	Liste p;
	p=l;
	int i=0;
	
	while (est_vide(p)==0) {
		printf("numero %d,  abscisse %d,  ordonnee %d\n", i, p->coord.abscisse, p->coord.ordonnee);
		i++;
		p=p->suiv;
	}

	return 0;
}

Liste ajout_tete(Maillon c, Liste l) {
	printf("\nentrée dans la fonction ajout_tete\n");
	if (est_vide(l)==1) {
		
		l=calloc(1,sizeof(*l));
	
		l->n = (l->n) + 1; //le serpent a grandi d'un élément
	
		l->coord.abscisse = c.coord.abscisse;
	
		l->coord.ordonnee = c.coord.ordonnee;
	
		l->suiv=NULL;

		return l;

	}
	
	Liste p = calloc(1,sizeof(*p));
	if (p==NULL) {
		printf("erreur lors de l'allocation d'une liste\n");
		return NULL;
	}

	printf("recopie des champs\n");
	
	p->n = (l->n) + 1;
	
	p->coord.abscisse = c.coord.abscisse;
	
	p->coord.ordonnee = c.coord.ordonnee;
	
	p->suiv=l;
	
	return p;	
}

Liste supprimer_tete(Liste l) {
	if (est_vide(l)==0) {
		Liste p;
		p=l->suiv;
		free (l);
		return p;
	}
	else {
		return NULL;
	}
}

Liste supprime_tout(Liste l) {
	printf("entrée dans supprime_tout\n");
	if (est_vide(l)==0)
	{	if (l->suiv == NULL) {
			printf("un seul élément dans la liste\n");
			l=supprimer_tete(l);
		}

		while (est_vide(l)==0) {
			l=supprimer_tete(l);
			l=l->suiv;
		}
	}	
	return l;

}





