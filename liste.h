#ifndef _LISTE_H_
#define _LISTE_H_


//la structure de base : les coordonnées
typedef struct coord_cachee {
	int abscisse;
	int ordonnee;
} COORDONNEES, POIS;

//la structure du serpent
typedef struct cellule {
	int n; //la taille du serpent
	COORDONNEES coord; //la position de la tête
	struct cellule* suiv;
} Maillon, *Liste;
typedef Liste SERPENT;

//le pois qu'il faut attraper
//typedef struct COORDONNEES POIS;



Liste creer_liste(void);

int est_vide(Liste l);

int visualiser_liste(Liste l);

Liste ajout_tete(Maillon c, Liste l);
 
Liste supprimer_tete(Liste l) ;

Liste supprime_tout(Liste l);








#endif






















/*typedef struct {
	unsigned int bp;
	char actif;
	unsigned int numero;
	char* commande;	// désassemblage de la ligne pointée par le bp
} breakpoint;



struct cellule {
	breakpoint element;
	struct cellule* suiv;
	};
typedef struct cellule Maillon;
typedef Maillon* Liste;*/



