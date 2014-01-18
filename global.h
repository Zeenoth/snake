#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//la structure des scores
typedef struct {
	int position;
	char player[25];
	int resultat;
} SCORE;

int SIZE;	//taille d'une case
int N;		//nombre de cases du tableau
int UT;		//base de temps en ms

#endif
