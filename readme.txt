Pour compiler, utiliser la commande make. Il faut avoir les bibliothèques
	SDL
	SDL_image
	SDL_draw
	SDL_ttf
Pour compiler sur les ordis de l'école, remplacer le makefile par le fichier "makefile ecole" présent dans le dossier makefiles.

Pour lancer le jeu, il suffit de le lancer en ligne de commande, il n'y a pas besoin de paramètres.

Par défaut, la fenêtre utilisée est une grille de N=10 cases de côté ; chaque case fait SIZE=70 pixels.
Ces paramètres sont des variables globales et sont modifiables dans le fichier main.c.

Avant d'entrer dans la boucle principale, plusieurs initialisations sont effectuées :
	initialisation de la bibliothèque SDL (mode video et mode audio)
	création du serpent. Il fait taille_serpent=3 cases. Il est positionné horizontalement, la queue au centre de l'écran.
	création du pois. Sa position est aléatoire mais il ne peut pas se trouver là où il y a déjà le serpent.
Ces fonctions sont dans le module init.h/init.c.

Les structures sont définies dans le fichier liste.h :
	COORDONNEES contient une abscisse et une ordonnée, exprimées en nombre de cases et non en pixels
	POIS est pareil que COORDONNEES
	SERPENT est une liste de structures contenant la taille du serpent, les COORDONNEES des segments, la direction dans laquelle il avance. On fait toujours référence à la tête du serpent ; d'ailleurs l'information sur la taille du serpent n'est correcte que dans le maillon de tête de la liste, elle n'est pas actualisée dans les autres maillons.
	VARIABLES contient toutes les autres valeurs nécessaires au fonctionnement du jeu : le score, si on a perdu, si le serpent a attrapé le pois, etc.

Il est possible d'afficher les coordonnées d'un pois ou du serpent avec les fonctions visualiser_liste() et visualiser_pois().

Lorsque la partie est finie, on ouvre le fichier contenant les scores et on les affiche.


AMÉLIORATIONS POSSIBLES

À chaque rafraîchissement d'écran le serpent scintille. Il faudrait que tous les segments s'affichent en même temps.
Afficher le texte dans la fenêtre et non dans le terminal.
Ajouter du son.
Faire différents modes de jeu :
	fastoche : pas de collisions sur les bords, le serpent revient de l'autre côté de l'écran
	normal
	hardcore : UT diminue régulièrement
	labyrinthe : des murs existent à l'intérieur de la grille
	dessin : il faut mettre le serpent dans une position dessinée sur la grille
Pouvoir combiner différents modes : hardcore avec les autres
	multijoueur : deux joueurs sur le même écran, une pomme chacun (à voir si on peut manger la pomme de l'autre, si ça nous fait perdre, ou si simplement on passe dessus et ça empêche l'autre de la prendre !)
