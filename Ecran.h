#ifndef CLASS_ECRAN
#define CLASS_ECRAN

#include <SFML/Graphics.hpp>
#include "ecrans.h"
#include "Personnage.h"
#include "Affichage.h"
#include "Carte.h"
#include "Son.h"
#include "Bombe.h"

class Ecran
{
public :
	Ecran();
	virtual int run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son) = 0;
};

#endif
