#include "Bombe.h"
using namespace std;

/**
 * Constructeur
 */
Bombe::Bombe(Carte *ptr_carte) : carte(ptr_carte){
	emplacementBombe = 0;
	positionX = 0;
	positionY = 0;
	force = 0;
}

/**
 * Récupère la position en pixel du personnage et la convertit en cases
 *
 * @Param float posX position en x de la bombe
 * @Param float posY position en y de la bombe
 * @Param float force puissance de la bombe
 *
 * @Return void
 */

void Bombe::position(float posX, float posY, int forceBombe) {
	positionX = int((posX+20)/40 - (70.f / 40.f));
	positionY = int((posY+20)/40 - (70.f / 40.f));
	force = forceBombe;
}
/**
 * Envoi les coordonnées de la bombe à carte
 *
 * @Return void
 */

void Bombe::poserBombe () {
   carte->bombePose(positionX, positionY);
}


/* --- Getters --- */

int Bombe::getEmplacementBombe()
{
	return emplacementBombe;
}

int Bombe::getPositionX()
{
	return positionX;
}

int Bombe::getPositionY()
{
	return positionY;
}

int Bombe::getForce()
{
	return force;
}

/* --- Setters --- */

void Bombe::setEmplacementBombe(int emplacementBombe)
{
	this->emplacementBombe = emplacementBombe;
}




