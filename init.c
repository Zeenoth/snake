#include "init.h"
#include "liste.h"
#include "fonctions.h"

#include <time.h>
#include <stdlib.h>

POIS init_pois(POIS p, int hauteur, int largeur) {
	
	srand(time(NULL)); //initialisation de la fonction random
	
	p.abscisse=rand()%largeur;
	p.ordonnee=rand()%hauteur;

	return p;
}

SERPENT init_serpent(SERPENT le_serpent, int taille_serpent, int hauteur, int largeur) {
	le_serpent = calloc(1, sizeof(*le_serpent));
	if (le_serpent == NULL) {
		printf("erreur d'initialisation\n");
		exit(0);
	}

	le_serpent->n = 1;
	le_serpent->direction = droite; //en début de partie il commence vers la droite
	le_serpent->coord.abscisse = floor(largeur/2); //il apparaît au centre de l'écran
	le_serpent->coord.ordonnee = floor(hauteur/2);

	while (le_serpent->n < taille_serpent) {
		le_serpent = grandit(le_serpent);
		//la fonction grandit() incrémente serpent->n
	}

	return le_serpent;
}
