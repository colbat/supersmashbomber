#include <SFML/Audio.hpp>
#include "Son.h"
#include "Carte.h"
#include "Bombe.h"
#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE

using namespace std;
class Personnage
{
public:
    /* --- Constructeurs --- */
	Personnage();
	Personnage(Carte *ptr_carte, int caseDepartX, int caseDepartY, sf::Key::Code toucheHaut, sf::Key::Code toucheDroite, sf::Key::Code toucheBas, sf::Key::Code toucheGauche, sf::Key::Code toucheBombe, int puissanceBombe, float tempsAttenteBombes);

    /* --- Méthodes ---*/
	void controlerPersonnage(const sf::Input &input, sf::RenderWindow &fenetre);
	void detectionCollision(sf::RenderWindow &fenetre);
	void poserBombe();
	void ramasserBonus(Carte *ptr_carte, Son *ptr_son);
	void animationDeplacement();
	bool affinageCollision(int coinX, int coinY);
	void initPersonnage();

    /* --- Getters --- */
	sf::Sprite& getSpritePersonnage();
    string getThemePersonnage();
	int getDirectionPersonnage() const;
	int getPhaseDeplacement() const;
	int getDernierSpriteAnim();
	int getNombreDeBombePossible();
	int getPuissanceBombes();
	int getVitesseDeplacement();
	int getTempsAttenteBombes();
	int getNombreDeManchesGagnantes();
	int getScoreActuel();
    static int getNombreDePersonnage();
	bool isVainqueurFinal();
	bool isBombePosee();
    bool isVivant() const;
	bool isActif() const;

    /* --- Setters --- */
	void setBombePosee(bool posee);
	void setVivant (bool vivant);
	void setActif(bool actif);
	void setNombreDeBombePossible(int nombre);
	void setThemePersonnage(std::string pTheme);
	void setNombreDeManchesGagnantes(int pNbManche);
	void setScoreActuel(int pScore);
	void setVainqueurFinal(bool vainqueur);

private:
	/* --- Pointeurs ---*/
	Carte *carte;

    /* --- Timers ---*/
    sf::Clock timerAnimation;
    sf::Clock timerTouche;

    /* --- Ressources personnage --- */
    string themePersonnage;
    sf::Sprite spritePersonnage;

	/* --- Case d'apparition du personnage --- */
	int caseDepartX;
	int caseDepartY;
    int indexPremierSpriteAnim; // Index du premier sprite de l'animation sur le tileset personnage
	int indexDernierSpriteAnim; // Index du dernier sprite de l'animation sur le tileset personnage

	/* --- Attributs scores --- */
	int scoreActuel;
	int nombreManchesGagnantes;

    /* --- Touches évènements ---*/
	sf::Key::Code toucheHaut;
	sf::Key::Code toucheDroite;
	sf::Key::Code toucheBas;
	sf::Key::Code toucheGauche;
	sf::Key::Code toucheBombe;

    /* --- Collisions --- */
	int caseCoinHautGauche;
	int caseCoinHautDroit;
	int caseCoinBasGauche;
	int caseCoinBasDroit;
	int caseCollisionX;
	int caseCollisionY;

    /* --- Etat du personnage ---*/
	int directionPersonnage;
	int phaseDeplacement;
	bool personnageEnVie;
	bool personnageVainqueurFinal;
	bool personnageActif;
	bool personnageSurBombe;
	bool bombePosee;
	bool nouvelleDirection; // Vrai quand le personnage change de direction

	/* --- Necessaire au bonus --- */
	float vitesseDeplacement;
    int puissanceBombe;
    float tempsAttenteBombes;


};
#endif
