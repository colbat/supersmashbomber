#include <SFML/Audio.hpp>
#include <queue>
#include "Carte.h"
#include "Personnage.h"
#include "Son.h"
#include "Bombe.h"
#ifndef DEF_BOMBESMANAGER
#define DEF_BOMBEBOMBESMANAGER

using namespace std;
class BombesManager
{
public:
	void traitementBombe(Personnage *ptr_personnage, Carte *ptr_carte, Son *ptr_son);
private:
    /* --- Timer ---*/
    sf::Clock timer;
    float tempsBombePosee;
    float tempsEcoule;

    /* --- Creation de la file contenant les bombes --- */
    queue<Bombe> qBombesExplosion;
    queue<Bombe> qBombesFinExplosion;

    /* --- Creation de la file servant au timer --- */
    queue<float> timerBombeExplosion;
    queue<float> timerBombeFinExplosion;
};

#endif


