#include <iostream>
#include "Ecran.h"
#include "BombesManager.h"

class EcranJeu : public Ecran
{
public:
    int run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son);
};
