Pour lancer le jeu, il suffit de le lancer en ligne de commande, il n'y a pas besoin de paramètres.

Par défaut, la fenêtre utilisée est une grille de N=10 cases de côté ; chaque case fait SIZE=70 pixels.
Ces paralètres sont modifiables dans le fichier global.h.

Avant d'entrer dans la boucle principale, plusieurs initialisations sont effectuées :
	initialisation de la bibliothèque SDL (mode video et mode audio)
	création du serpent. Il fait taille_serpent=3 cases. Il est positionné horizontalement, la queue au centre de l'écran.
	création du pois. Sa position est aléatoire.
Ces fonctions sont dans le module init.h/init.c.

Les structures sont définies dans le fichier liste.h :
	COORDONNEES contient une abscisse et une ordonnées, exprimées en nombre de cases et non en pixels
	POIS est pareil que COORDONNEES
	SERPENT est une liste de structures contenant la taille du serpent, les COORDONNEES des segments, la direction dans laquelle il avance. On fait toutjours référence à la tête du serpent ; d'ailleurs l'information sur la taille du serpent n'est correcte que dans le maillon de tête de la liste, elle n'est pas actualisée dans les autres maillons.

Il est possible d'afficher les coordonnées d'un pois ou du serpent avec les fonctions visualiser_liste() et visualiser_pois().
