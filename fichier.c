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

int merite(int s, SCORE* t) {
	int i = 10; //le tableau des scores fait 10 cases, on le parcourt depuis la fin
	printf("dernier %d\n", t[i].resultat);
	printf("toi %d\n", s);

	if (s < t[i].resultat) { //cas où le joueur ne fait pas partie des meilleurs
		return 20;
	}
	
	if (s == t[i].resultat) { //cas où il est dernier
		return i;
	}

	else {
		i--;
		while (i >= t[i].resultat) {
			i--;
		}
	}
	
	return i+2;
}

void ecrit_score(int s, FILE* fichier) {


	
}





