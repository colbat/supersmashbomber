#include <iostream>
#include "Ecran.h"

class EcranMenu : public Ecran
{
public:
	EcranMenu();
    int run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son);

private:
    bool unJoueur;
    bool multi;
    bool quitter;

	sf::Image Image;
	sf::Image ImageUnJoueur;
	sf::Image ImageMulti;
	sf::Image ImageQuitter;
	sf::Image ImageUnJoueurJ;
	sf::Image ImageMultiJ;
	sf::Image ImageQuitterJ;

	sf::Sprite Sprite;
	sf::Sprite SpriteUnJoueur;
	sf::Sprite SpriteMulti;
	sf::Sprite SpriteQuitter;
	sf::Sprite SpriteUnJoueurJ;
	sf::Sprite SpriteMultiJ;
	sf::Sprite SpriteQuitterJ;

};
