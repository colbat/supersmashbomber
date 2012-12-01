#include "Affichage.h"
#define TILES_X_CARTE 10
#define TILES_X_PERSO 12
#define DECALAGE 70

/**
 * Constructeur par défaut
 */
Affichage::Affichage()
{
}

/**
 * Constructeur
 * Prend en paramètre un pointeur vers Carte ( pour le lien ) et un theme de type String.
 */
Affichage::Affichage(Carte *ptr_carte) : carteJeu(ptr_carte)
{
	// Theme de la carte par défaut
	themeCarte = "zelda";
}

/**
 * Méthode pour charger les images du theme voulu
 *
 * @Return void
 */
void Affichage::chargerThemeCarte()
{
	// Chemin du tileset de la carte en fonction du nom du theme
	std::string pathCarte = "tilesets/" + themeCarte + ".bmp";
	// Chemin de l'image de fond (bord de la carte) en fonction du nom du theme
	std::string pathFond = "tilesets/" + themeCarte + "Fond.bmp";

	// Chemin de l'image en fonction du nom du theme
	std::string pathMancheFinie = "tilesets/mancheFinie.bmp";
	// Chemin de l'image en fonction du nom du theme
	std::string pathMancheEgalFinie = "tilesets/mancheEgalFinie.bmp";
	// Chemin de l'image en fonction du nom du theme
	std::string pathJeuFini = "tilesets/partieFinie.bmp";

	// Chargement image carte
	if(!imageCarte.LoadFromFile(pathCarte.c_str()))
		std::cout << "Erreur de chargement de l'image carte..." << std::endl;

	// Chargement image fond
	if(!imageFond.LoadFromFile(pathFond.c_str()))
		std::cout << "Erreur de chargement de l'image fond..." << std::endl;

	// Chargement image fin de manche
	if(!imageMancheFinie.LoadFromFile(pathMancheFinie.c_str()))
	{
		std::cout << "Erreur de chargement de l'image de manche finie" << std::endl;
	}

	// Chargement image fin de manche égalité
	if(!imageMancheEgalFinie.LoadFromFile(pathMancheEgalFinie.c_str()))
	{
		std::cout << "Erreur de chargement de l'image de manche egal finie" << std::endl;
	}

	// Chargement image fin de partie
	if(!imageJeuFini.LoadFromFile(pathJeuFini.c_str()))
	{
		std::cout << "Erreur de chargement de l'image de jeu fini" << std::endl;
	}

	imageCarte.SetSmooth(false);

	// Chargement des sprites
	spriteCarte.SetImage(imageCarte);
	spriteFond.SetImage(imageFond);
	spriteMancheFinie.SetImage(imageMancheFinie);
	spriteMancheEgalFinie.SetImage(imageMancheEgalFinie);
	spriteJeuFini.SetImage(imageJeuFini);
}

/**
 * Méthode pour charger les images du personnage
 *
 * @Param Personnage &perso1
 * @Param Personnage &perso2
 *
 * @Return void
 */
void Affichage::chargerThemePersonnage(Personnage &perso1, Personnage &perso2)
{
	// Thème du personnage
	std::string themePerso1 = perso1.getThemePersonnage().c_str();
	std::string themePerso2 = perso2.getThemePersonnage().c_str();

	// Chemin de l'image en fonction du nom du theme
	std::string pathPerso1 = "tilesets/" + themePerso1 + "Perso.png";
	// Chemin de l'image en fonction du nom du theme
	std::string pathPerso2 = "tilesets/" + themePerso2 + "Perso.png";

	// Chemin de l'image en fonction du nom du theme
	std::string pathPerso1Score = "tilesets/" + themePerso1 + "PersoScore.png";
	// Chemin de l'image en fonction du nom du theme
	std::string pathPerso2Score = "tilesets/" + themePerso2 + "PersoScore.png";

	// Chargement image personnage
	if(!imagePerso1.LoadFromFile(pathPerso1.c_str()))
	{
		std::cout << "Erreur de chargement de l'image perso 1" << std::endl;
		// On remet le thème de zelda si il y a une erreur lors du chargement d'un autre thème
		perso1.setThemePersonnage("zelda");
	}

	// Chargement image personnage
	if(!imagePerso2.LoadFromFile(pathPerso2.c_str()))
	{
		std::cout << "Erreur de chargement de l'image perso 2" << std::endl;
		// On remet le thème de zelda si il y a une erreur lors du chargement d'un autre thème
		perso2.setThemePersonnage("zelda");
	}

	// Chargement image personnage
	if(!imagePerso1Score.LoadFromFile(pathPerso1Score.c_str()))
	{
		std::cout << "Erreur de chargement de l'image perso 1 score" << std::endl;
	}

	// Chargement image personnage
	if(!imagePerso2Score.LoadFromFile(pathPerso2Score.c_str()))
	{
		std::cout << "Erreur de chargement de l'image perso 2 score" << std::endl;
	}

	// Chargement des sprites
	perso1.getSpritePersonnage().SetImage(imagePerso1);
	perso2.getSpritePersonnage().SetImage(imagePerso2);
	spritePerso1Score.SetImage(imagePerso1Score);
	spritePerso2Score.SetImage(imagePerso2Score);
}

/**
 * Chargement des polices de caractères
 *
 * @Param std::string police
 * @Param float tailleCaractere
 *
 * @Return void
 */
void Affichage::chargerPoliceCaractere(std::string police, float tailleCaractere)
{
	std::string pathPolice = "tilesets/" + police;

	// Chargement de la police de caractère à partir d'un fichier
	if (!texteFont.LoadFromFile(pathPolice.c_str(), tailleCaractere))
		std::cout << "Erreur de chargement de la police de caractère...." << std::endl;
}

/**
 * Affichage du fond
 *
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */
void Affichage::displayFond(sf::RenderWindow &fenetre)
{
	// Chargement du sprite fond ( bords de la carte )
	fenetre.Draw(spriteFond);
}

/**
 * Affichage des sprites pour chaques cases dans la fenetre
 *
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */
void Affichage::displayMap(sf::RenderWindow &fenetre)
{
	int coordGauche = 0;
	int coordHaut = 0;
	int coordDroite = 0;
	int coordBas = 0;

	// Tableau local mis à zéro
	int tableau[15][15] = {0, 0};

	// Boucle sur le tableau local pour le remplir en fonction de TableauCarte
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			// On récupère le tableau de la classe Carte pour mettre à jour le tableau local
			 tableau[i][j] = carteJeu->getTableauCarte(i, j);

			// Coordonnées pour prendre le bon tile en fonction du nombre de tiles horizontal sur le tileset
			coordGauche = (tableau[i][j] % TILES_X_CARTE) * 40;
			coordHaut = (tableau[i][j] / TILES_X_CARTE) * 40;
			coordDroite = coordGauche + 40;
			coordBas = coordHaut + 40;

			// Decoupage du tileset en fonction du sprite voulu
			spriteCarte.SetSubRect(sf::IntRect(coordGauche, coordHaut, coordDroite, coordBas));
			// Mise en place du sprite au bon endroit dans la fenetre
			spriteCarte.SetPosition(j*40.f + DECALAGE, i*40.f + DECALAGE);
			// On affiche le tileset découpé pour le tile voulu
			fenetre.Draw(spriteCarte);
		}
	}
}

/**
 * Méthode d'affichage des personnage
 *
 * @Param Personnage *ptr_personnage
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */
void Affichage::displayPerso(Personnage *ptr_personnage, sf::RenderWindow &fenetre)
{
	// Coordonnées pour prendre le bon tile en fonction du nombre de tiles horizontal sur le tileset personnage et de la phase d'animation
	int coordGauchePerso = (ptr_personnage->getPhaseDeplacement() % TILES_X_PERSO) * 40;
	int coordHautPerso = (ptr_personnage->getPhaseDeplacement() / TILES_X_PERSO) * 40;
	int coordDroitePerso = coordGauchePerso + 40;
	int coordBasPerso = coordHautPerso + 40;

	// Decoupage du tileset en fonction du sprite voulu
	ptr_personnage->getSpritePersonnage().SetSubRect(sf::IntRect(coordGauchePerso, coordHautPerso, coordDroitePerso, coordBasPerso));

	// On affiche le tileset découpé pour le tile voulu
	fenetre.Draw(ptr_personnage->getSpritePersonnage());
}

/**
 * Affichage du personnage gagnant ou perdant
 *
 * @Param Personnage *ptr_personnage
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */
void Affichage::displayPersoFini(Personnage *ptr_personnage, sf::RenderWindow &fenetre)
{
	// Test quel personnage est gagnant ou perdant et découpage du sprite en fonctionde cela
	if(ptr_personnage->isVivant())
		ptr_personnage->getSpritePersonnage().SetSubRect(sf::IntRect(523, 0, 560, 40));
	else
		ptr_personnage->getSpritePersonnage().SetSubRect(sf::IntRect(480, 0, 520, 40));

	// On affiche les personnages
	fenetre.Draw(ptr_personnage->getSpritePersonnage());
}

/**
 * Méthode pour afficher les avatars des personnages
 *
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */

void Affichage::displayAvatar(sf::RenderWindow &fenetre) {

    spritePerso1Score.SetPosition(90, 690);
    spritePerso2Score.SetPosition(400, 690);
    fenetre.Draw(spritePerso1Score);
    fenetre.Draw(spritePerso2Score);
}
/**
 * Méthode pour afficher les scores des personnages
 *
 * @Param sf::RenderWindow &fenetre
 * @Param Personnage &perso
 * @Param float positionX
 *
 * @Return void
 */
void Affichage::displayScore(sf::RenderWindow &fenetre, Personnage &perso ,float positionX)
{
    std::ostringstream intToString;
	/* --- Score: puissance bombe --- */
    intToString << perso.getPuissanceBombes();
    // Paramêtres de texte
	bonus1.SetColor(sf::Color(0, 0, 0));
    bonus1.SetFont(texteFont);
	bonus1.SetText(intToString.str());
	bonus1.SetSize(20);
	bonus1.SetPosition(positionX+100, 708);
	/* --- Score: vitesse --- */
	intToString.str("");
	int vitesseDeplacement = perso.getVitesseDeplacement()- 150;
	vitesseDeplacement = (vitesseDeplacement/50)+1;
	intToString <<vitesseDeplacement;
	// Paramêtres de texte
	bonus2.SetColor(sf::Color(0, 0, 0));
    bonus2.SetFont(texteFont);
	bonus2.SetText(intToString.str());
	bonus2.SetSize(20);
	bonus2.SetPosition(positionX+157, 708);
	/* --- Score : fréquence bombe ---*/
    intToString.str("");
	intToString << perso.getTempsAttenteBombes();
	// Paramêtres de texte
	bonus3.SetColor(sf::Color(0, 0, 0));
    bonus3.SetFont(texteFont);
	bonus3.SetText(intToString.str());
	bonus3.SetSize(20);
	bonus3.SetPosition(positionX+218, 708);

	// Options du texte
    intToString.str("");
	intToString << perso.getScoreActuel();
	score.SetColor(sf::Color(0, 0, 0));
	score.SetFont(texteFont);
	score.SetText(intToString.str());
	score.SetSize(30);
	score.SetPosition(positionX+260, 700);

	// On affiche le tout
	fenetre.Draw(bonus1);
	fenetre.Draw(bonus2);
	fenetre.Draw(bonus3);
	fenetre.Draw(score);
}

/**
 * Affichage d'un sprite quand une manche est finie
 *
 * @Param sf::RenderWindow &fenetre
 * @Param std::string nJoueur
 * @Param float positionX
 * @Param float positionY
 *
 * @Return void
 */
void Affichage::displayFinManche(sf::RenderWindow &fenetre, std::string nJoueur, float positionX, float positionY)
{
	numeroJoueur.SetFont(texteFont);
	numeroJoueur.SetColor(sf::Color(0, 0, 0));
	numeroJoueur.SetText(nJoueur);
	numeroJoueur.SetPosition(positionX + 405, positionY + 8);

	// Options du sprite
	spriteMancheFinie.SetPosition(positionX, positionY);

	// Affichage dans la fenetre
	fenetre.Draw(spriteMancheFinie);
	fenetre.Draw(numeroJoueur);
}

/**
 * Affichage d'un sprite quand une manche égalité est finie
 *
 * @Param sf::RenderWindow &fenetre
 * @Param float positionX
 * @Param float positionY
 *
 * @Return void
 */
void Affichage::displayFinMancheEgal(sf::RenderWindow &fenetre, float positionX, float positionY)
{
    //option du sprite
    spriteMancheEgalFinie.SetPosition(positionX, positionY);

    //affichage dans la fenetre
    fenetre.Draw(spriteMancheEgalFinie);
}

/**
* Affichage d'un sprite quand une partie est finie
 *
 * @Param sf::RenderWindow &fenetre
 * @Param std::string nJoueur
 * @Param float positionX
 * @Param float positionY
 *
 * @Return void
 */
void Affichage::displayFinJeu(sf::RenderWindow &fenetre, std::string nJoueur, float positionX, float positionY)
{
	numeroJoueur.SetFont(texteFont);
	numeroJoueur.SetColor(sf::Color(0, 0, 0));
	numeroJoueur.SetText(nJoueur);
	numeroJoueur.SetPosition(positionX + 405, positionY + 8);

	// Options du sprite
	spriteJeuFini.SetPosition(positionX, positionY);

	// Affichage dans la fenetre
	fenetre.Draw(spriteJeuFini);
	fenetre.Draw(numeroJoueur);

}

/* --- Setters --- */
void Affichage::setThemeCarte(std::string cTheme)
{
	themeCarte = cTheme;
}

/* --- Getters --- */
std::string Affichage::getThemeCarte()
{
	return themeCarte;
}

