#ifndef DEF_BOMBE
#define DEF_BOMBE

#include <SFML/Audio.hpp>
#include <string>
#include "Carte.h"
#include <iostream>
#include "Personnage.h"
#include "Son.h"

class Bombe
{
public:
    /* --- Constructeur --- */
	Bombe(Carte *ptr_carte);

	/* --- Méthodes --- */
    void position(float posX, float posY, int forceBombe );
	void positionTest();
	void poserBombe ();

	/* --- Getters --- */
	int getEmplacementBombe();
	int getPositionX();
	int getPositionY();
	int getForce();

	/* --- Setters --- */
	void setEmplacementBombe(int emplacementBombe);

private:
    /* --- Pointeurs ---*/
    Carte *carte;
    /* --- Attributs Bombe --- */
	int emplacementBombe;
    int positionX;
    int positionY;
	int force;
};

#endif

