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

	fclose(fichier);

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
	int i = 9; //le tableau des scores fait 10 cases, on le parcourt depuis la fin
	//printf("dernier %d\n", t[i].resultat);
	//printf("toi %d\n", s);

	if (s < t[i].resultat) { //cas où le joueur ne fait pas partie des meilleurs
		return 20;
	}
	
	if (s == t[i].resultat) { //cas où il est dernier
		return i+1;
	}

	else {
		while (s >= t[i].resultat) {
			i--;
		}
		
	}

	if (i+2 < 1) { //c'est parce que ça bug dès qu'on est meilleur que le premier
		i = -1;
	}
	
	return i+2;
}

void ecrit_score(int classement, int points, FILE* fichier, SCORE* tableau) {
	printf("entrée dans la fonction ecrit_score\n");

	printf("Quel est ton prénom ? (Ne pas mettre d'espace)\n");
	char prenom[255];
	scanf("%s", prenom);

	printf("ton nom est %s\n", prenom);

	//on va écraser le fichier existant
	fichier = fopen("score.txt", "w");
	
	int i = 1; //indice qui parcourt les scores

	//on écrit tous les scores avant celui du joueur tels quels
	while (i < classement) {
		fprintf(fichier, "%s %d\n", tableau[i-1].player, tableau[i-1].resultat);
		i++;
	}
	//maintenant on se trouve à la position i = classement
	fprintf(fichier, "%s %d\n", prenom, points);

	//maintenant on reprend jusqu'à la 9ème position (le 10 s'est fait éjecter)
	//i++;
	
	while (i < 10) {
		fprintf(fichier, "%s %d\n", tableau[i-1].player, tableau[i-1].resultat);
		i++;
	}

	fclose(fichier);
	
}





