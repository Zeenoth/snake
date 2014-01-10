/******************************************************************/
			/*STRUCTURES*/

struct coord {
	int abs; // <W
	int ord; // <H
	};
typedef struct coord COORDONNEES;

typedef struct liste* LISTE_POS;
struct liste { //liste des n coordonnées occupées par la tête
	int abs;
	int ord;
	LISTE_POS suiv;
	};


struct pois {
	int abs;
	int ord;
	};
typedef struct pois POIS;


struct serpent {
	int n; //longueur du serpent
	int abs_serp;
	int ord_serp;
	LISTE_POS pos_anterieures; //cette liste ne doit pas dépasser n maillons
	};
typedef struct serpent SERPENT;

/******************************************************************/
			/*FONCTIONS SUR LES STRUCTURES*/

LISTE_POS creer_liste(void);

int est_vide(LISTE_POS l);

LISTE_POS ajouter_tete(COORDONNEES c, LISTE_POS l);

LISTE_POS ajouter_queue(COORDONNEES c, LISTE_POS l);

LISTE_POS supprimer_queue(LISTE_POS l);

void voir_coord(COORDONNEES c); //visualise un couple de coord

void voir_pois(POIS p); //la même mais pour un pois

void voir_serpent(SERPENT s);

void voir_liste(LISTE_POS l);






