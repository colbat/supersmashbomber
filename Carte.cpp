#include "Carte.h"
using namespace std;

/**
 * CONSTRUCTEUR de la classe
 * initialisation du tableau de 15 cases par 15
 * avec des valeurs egales a 0
 */
Carte::Carte()
{
	// Initialisation à VIDE des cases du tableau de la carte
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
			tab[i][j] = VIDE;
	}
	// Initialisation à VIDE de cases du tableau des bonus
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
			tabBonus[i][j] = VIDE;
	}

}

/**
 * Remplissage du tableau de 15 cases par 15
 * depuis un fichier de carte
 *
 * @Param string nomFichier nom du fichier carte
 *
 * @Return void
 */
void Carte::initCarte(string nomFichier)
{

	//ouverture du fichier
	ifstream fichier(nomFichier.c_str());
	int caractereActuel = 0;

	//Si le fichier s'est correctement ouvert
	if (fichier != NULL)
	{

		//Boucle qui lit tous les caracteres du fichier level et les place dans le tableau
		for(int i = 0; i < 15; i++)
		{
			for(int j = 0; j < 15; j++)
			{
				fichier >> caractereActuel;
				tab[i][j] = caractereActuel;
			}
		}

		//Fermeture du fichier
		fichier.close ();
	}
	else
	{
		//Afficher une erreur si le fichier ne se charge pas
		cout << "## Erreur lors de l'ouverture du fichier de carte##";
	}
}
/**
 * Initialisation du tableau contenant les emplacement de bonus cachés
 *
 * @Param int freqBonus fréquence d'apparition des bonus en pourcentage
 *
 * @Return void
 */

void Carte::initBonus(int freqBonus) {

    // Initialisation à VIDE de cases du tableau des bonus
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
			tabBonus[i][j] = VIDE;
	}
	int nbCaisses = 0;
	// On boucle le tableau afin de connaitre le nombre de caisses
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if (tab[i][j] == CAISSE)
			{
				nbCaisses ++;
			}
		}
	}
	// On calcul le nombre de bonus en fonction du nombre de caisses et du pourcentage souhaitté
	int nbBonus = (nbCaisses * freqBonus / 100);
	/* On initialise la taille maximum du tableau contenant les chiffres aléatoires correspondant aux caisses
       qui contiendront des bonus */
	int tabMax = nbBonus - 1;
	// Création pointeur pour allocation dynamique de tableau
	int *tabRandom = NULL;
	// Libération de la mémoire 
	delete[] tabRandom;
	// Allocation mémoire pour le tableau des bonus
	tabRandom = new int[tabMax];

	// Initialisation du tableau des nombres aléatoires
	for(int i = 0; i < tabMax; i++) {
		tabRandom[i] = 0;
	}
	// On declare une variable servant à contenir les nombres aléatoires
	int random = 0;
	// On déclare un booléen qui sera vrai si un nombre à deja été généré
	bool sameRandom = true;

	// On rempli le tableau avec des nombres aléatoires tous différents
	for ( int index = 0; index <= tabMax;index++) {
		// Tant que le nombre généré est contenu dans le tableau des nombre deja générés
		while (sameRandom) {
			sameRandom = false;
			// On génère un nombre aléatoire
			random = sf::Randomizer::Random(0,nbCaisses);
			for (int i = 0; i <= index ; i++) {
				// Si le nombre génré est présent dans le tableau
				if (tabRandom[i] == random) {
					sameRandom = true;
				}
			}
		}
		// Si le nombre n'a pas deja été généré alors on l'enregistre
		tabRandom[index] = random;
		sameRandom = true;
		// Debug
		std::cout << tabRandom[index] << " | " ;
	}
	// Debug
	std::cout <<endl << "-----------------------------------" << endl;
	// On déclare une variable servant à connaitre le numero de la caisse actuel
	int caisseIndex = 0;
    // On rempli le tableau des bonus
    for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if (tab[i][j] == CAISSE)
			{
				caisseIndex ++;
				for (int k = 0 ; k <= tabMax; k++)
				{
					if (caisseIndex == tabRandom[k])
					{
						int randomBonus = 0;
						randomBonus = sf::Randomizer::Random(6,9);
						tabBonus[i][j] = randomBonus;
					}
				}
			}
		}
	}
	// Debug (parcours du tableau des bonus)
	std::cout << "Tableau des bonus : " << endl ;
	std::cout << "-----------------------------------"<<endl;
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			std::cout << tabBonus[i][j] <<"|";
		}
		std::cout<<endl;
	}
}

/**
 * Pose d'une bombe sur la carte
 *
 * @Param int x : position en x de la bombe posee
 * @Param int y : position en y de la bombe posee
 *
 * @Return void
 */
void Carte::bombePose(int x, int y)
{
	tab[y][x] = BOMBE;
}



/**
 * Pose d'un bonus sur la carte
 *
 * @Param int x position en x du bonus pose
 * @Param int y position en y du bonus pose
 * @Param int bonus indique le type de bonnus pose (PUISSANCE, VITESSE, ect..)
 *
 * @Return void
 */
void Carte::bonusPose(int x, int y, int bonus)
{
	tab[x][y] = bonus;
}



/**
 * Explosion d'une bombe sur la carte
 *
 * @Param int x : position en x de l'explosion
 * @Param int y : position en y de l'explosion
 * @Param int puissanceBombe indique la puissance de l'explosion
 *                           afin de determiner le nombre de caisse a exploser
 *
 * @Return void
 */
void Carte::explosion(int x, int y, int puissanceBombe, bool phase)
{
	bool explosionG = true;
	bool explosionD = true;
	bool explosionH = true;
	bool explosionB = true;

	for(int i = 1; i <= puissanceBombe; i++)
	{
		//Explosion vers la gauche
		if(tab[y][x-i] != MUR && explosionG == true)
		{
			if ((x-i) >= 0)
			{
				switch(phase)
				{
				case true:
					tab[y][x-i] = EXPLOSION;
					tab[y][x] = EXPLOSION;
					break;

				case false:
					if (tabBonus[y][x-i] == PUISSANCE || tabBonus[y][x-i] == VITESSEPLUS || tabBonus[y][x-i] == NOMBREBOMBE || tabBonus[y][x-i] == VITESSEMOISNS)
					{
						tab[y][x - i] = tabBonus[y][x - i];
						tab[y][x] = tabBonus[y][x];
						tabBonus[y][x - i] = 0;
						tabBonus[y][x] = 0;
					}
					else
					{
						tab[y][x-i] = VIDE;
						tab[y][x] = VIDE;
						break;
					}
				}
			}
		}
		else{explosionG = false;}
		//Explosion vers la droite
		if(tab[y][x+i] != MUR  && explosionD == true)
		{
			if((x+i) <= 14)
			{
				switch(phase)
				{
				case true:
					tab[y][x+i] = EXPLOSION;
					tab[y][x] = EXPLOSION;
					break;

				case false:
					if (tabBonus[y][x+i] == PUISSANCE || tabBonus[y][x+i] == VITESSEPLUS || tabBonus[y][x+i] == NOMBREBOMBE || tabBonus[y][x+i] == VITESSEMOISNS)
					{
						tab[y][x + i] = tabBonus[y][x + i];
						tab[y][x] = tabBonus[y][x];
						tabBonus[y][x + i] = 0;
						tabBonus[y][x] = 0;
					}
					else {
						tab[y][x+i] = VIDE;
						tab[y][x] = VIDE;
						break;
					}
				}
			}
		}
		else{explosionD = false;}
		//Explosion vers le bas
		if(tab[y+i][x] != MUR && explosionB == true)
		{
			if((y+i) <= 14)
			{
				switch(phase)
				{
				case true:
					tab[y+i][x] = EXPLOSION;
					tab[y][x] = EXPLOSION;
					break;

				case false:
					if (tabBonus[y + i][x] == PUISSANCE || tabBonus[y + i][x] == VITESSEPLUS || tabBonus[y + i][x] == NOMBREBOMBE || tabBonus[y + i][x] == VITESSEMOISNS)
					{
						tab[y + i][x] = tabBonus[y + i][x];
						tab[y][x] = tabBonus[y][x];
						tabBonus[y + i][x] = 0;
						tabBonus[y][x] = 0;
					}
					else {
						tab[y+i][x] = VIDE;
						tab[y][x] = VIDE;
						break;
					}
				}
			}
		}
		else{explosionB = false;}


		//Explosion vers le haut
		if(tab[y-i][x] != MUR && explosionH == true)
		{
			if((y-i) >= 0)
			{
				switch(phase)
				{
				case true:
					tab[y-i][x] = EXPLOSION;
					tab[y][x] = EXPLOSION;
					break;

				case false:
					if (tabBonus[y - i][x] == PUISSANCE || tabBonus[y - i][x] == VITESSEPLUS || tabBonus[y - i][x] == NOMBREBOMBE || tabBonus[y - i][x] == VITESSEMOISNS)
					{
						tab[y - i][x] = tabBonus[y - i][x];
						tab[y][x] = tabBonus[y][x];
						tabBonus[y - i][x] = 0;
						tabBonus[y][x] = 0;
					}
					else {
						tab[y-i][x] = VIDE;
						tab[y][x] = VIDE;
						break;
					}
				}
			}
		}
		else{explosionH = false;}
	}
}

void Carte::effacerBonus(int x, int y)
{
	tab[x/40][y/40] = VIDE;
}

/* ---- Getters ---- */
int Carte::getTableauCarte(int i, int j)
{
	return tab[i][j];
}
/* ---- Setters ---- */
void Carte::setTableauCarte(int i, int j, int valeur)
{
    tab[i][j] = valeur;
}

