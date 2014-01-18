#include "fichier.h"


SCORE* charge_scores(FILE* fichier, SCORE* tab) {
	printf("\nChargement du tableau des scores\n");
	
	int i = 0; //entier qui compte les positions dans les scores
	char* mot = NULL;
	char ligne[512];
	const char* delim = " ";

	while (fgets(ligne, 512, fichier) != NULL) {
		i++;
		
		//premier mot : le nom du joueur
		mot = strtok(ligne, delim);
		strcpy(tab[i-1].player, mot);
		
		//deuxième mot : le score
		mot = strtok(NULL, delim);
		tab[i-1].resultat = atoi(mot);
	}

	return tab;
}

int affiche_scores(SCORE* t) {
	int i;

	printf("\nPalmarès :\n");
	for (i = 0 ; i<10 ; i++) {
		printf("%.2d %s : %d\n", i+1, t[i].player, t[i].resultat);
	}
	return 0;
}
