#include <iostream>
#include "Ecran.h"

class EcranMenuMulti : public Ecran
{
public:
	EcranMenuMulti();
    int run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son);

private :
	std::string joueur1;
	std::string joueur2;
	std::string map;

    sf::Image ImagePerso;
    sf::Image ImageMulti;
    sf::Image ImageFlecheDroite;
    sf::Image ImageFlecheGauche;
    sf::Image ImageMap;
    sf::Image ImageNombreManches;

    sf::Sprite SpriteMulti;
    sf::Sprite SpritePerso1;
    sf::Sprite SpritePerso2;
    sf::Sprite SpriteMap;
    sf::Sprite SpriteNombreManches;
    sf::Sprite SpriteFlecheDroite1;
    sf::Sprite SpriteFlecheDroite2;
    sf::Sprite SpriteFlecheDroite3;
    sf::Sprite SpriteFlecheDroite4;
    sf::Sprite SpriteFlecheGauche1;
    sf::Sprite SpriteFlecheGauche2;
    sf::Sprite SpriteFlecheGauche3;
    sf::Sprite SpriteFlecheGauche4;
    sf::Sprite SpriteFlecheGauche5;
};


