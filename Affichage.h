#ifndef DEF_AFFICHAGE
#define DEF_AFFICHAGE

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include "Carte.h"
#include "Personnage.h"
#include "Affichage.h"

class Affichage
{
public:
	Affichage();
	Affichage(Carte *ptr_carte);
	void chargerThemeCarte();
	void chargerThemePersonnage(Personnage &perso1, Personnage &perso2);
	void chargerPoliceCaractere(std::string police, float tailleCaractere);
	void displayFond(sf::RenderWindow &fenetre);
	void displayMap(sf::RenderWindow &fenetre);
	void displayPerso(Personnage *ptr_personnage, sf::RenderWindow &fenetre);
    void displayPersoFini(Personnage *ptr_personnage, sf::RenderWindow &fenetre);
	void displayAvatar(sf::RenderWindow &fenetre);
	void displayScore(sf::RenderWindow &fenetre, Personnage &perso, float positionX);
	void displayFinManche(sf::RenderWindow &fenetre, std::string nJoueur, float positionX, float positionY);
	void displayFinMancheEgal(sf::RenderWindow &fenetre, float positionX, float positionY);
	void displayFinJeu(sf::RenderWindow &fenetre, std::string nJoueur, float positionX, float positionY);

	/* Setters */
	void setThemeCarte(std::string cTheme);

	/* Getters */
	std::string getThemeCarte();

private:
	// Pointeur vers Carte, de cette façon on n'instancie pas l'objet.
	Carte *carteJeu;
    /* --- Score --- */
    sf::Font texteFont;
	sf::String bonus1;
	sf::String bonus2;
	sf::String bonus3;
	sf::String score;
	// Fin de partie
	sf::String numeroJoueur;
	sf::Image imageMancheFinie;
	sf::Image imageMancheEgalFinie;
	sf::Image imageJeuFini;
	sf::Sprite spriteMancheFinie;
	sf::Sprite spriteMancheEgalFinie;
	sf::Sprite spriteJeuFini;
    // Avatars
    sf::Image imagePerso1Score;
	sf::Image imagePerso2Score;
	sf::Sprite spritePerso1Score;
	sf::Sprite spritePerso2Score;

	/* --- Carte --- */
	sf::Image imageCarte;
	sf::Image imageFond;
    // Sprites des personnages
	sf::Image imagePerso1;
	sf::Image imagePerso2;
    // Sprites de la carte
	sf::Sprite spriteCarte;
	// Background
	sf::Sprite spriteFond;
    // String contenant le thème à charger
    std::string themeCarte;

};
#endif
