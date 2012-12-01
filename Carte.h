#ifndef DEF_CARTE
#define DEF_CARTE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

#define VIDE 0
#define HERBE 1
#define MUR 2
#define CAISSE 3
#define BOMBE 4
#define EXPLOSION 5
#define VITESSEPLUS 6
#define VITESSEMOISNS 7
#define PUISSANCE 8
#define NOMBREBOMBE 9


class Carte
{

public:
    /* --- Constructeur --- ¨*/
	Carte();
	/* --- Methode --- */
    void initCarte(std::string nomFichier);
    void initBonus(int freqBonus);
	void bombePose(int x, int y);
	void bonusPose(int x, int y, int bonus);
	void explosion(int x, int y, int puissanceBombe, bool phase);
	void effacerBonus(int x, int y);

	/* --- Getters --- */
	int getTableauCarte(int i, int j);
	/* --- Setters --- */
	void setTableauCarte(int i, int j, int valeur);

private:
	int tab[15][15];
	int tabBonus[15][15];
    int nbCaisses;
};
#endif
