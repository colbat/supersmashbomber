#include <iostream>
#include "Ecran.h"

class EcranMancheFinie : public Ecran
{
public:
    int run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son);
};
