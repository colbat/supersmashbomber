#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ecran.h"
#include "EcranMenu.h"
#include "EcranMenuMulti.h"
#include "EcranJeu.h"
#include "EcranMancheFinie.h"
#include "EcranJeuFini.h"

int main()
{
	// Ecran de lancement
	int ecranActuel = 0;
	// Liste des diff�rents �crans du jeu
	std::vector<Ecran*> vectorEcrans;
	// Cr�ation de la fen�tre principale
	sf::RenderWindow fenetre(sf::VideoMode(740, 740, 32), "SuperSmashBomber", sf::Style::Close);

	/* --- Cr�ation des �crans du jeu --- */
	EcranMenu eMenu;
	EcranMenuMulti eMenuMulti;
	EcranJeu eJeu;
	EcranMancheFinie eMancheFinie;
	EcranJeuFini eJeuFini;

	/* --- Cr�ation des �l�ments du jeu --- */
    Son son;
	Carte carteJeu;
	Affichage affichage(&carteJeu);
	Personnage perso1(&carteJeu, 0, 0, sf::Key::Up, sf::Key::Right, sf::Key::Down, sf::Key::Left, sf::Key::Space,3, 3.0);
	Personnage perso2(&carteJeu, 14, 14, sf::Key::Z, sf::Key::D, sf::Key::S, sf::Key::Q, sf::Key::E, 3, 3.0);

	/* --- Introduction des �crans dans la liste --- */
	vectorEcrans.push_back(&eMenu);
	vectorEcrans.push_back(&eMenuMulti);
	vectorEcrans.push_back(&eJeu);
	vectorEcrans.push_back(&eMancheFinie);
	vectorEcrans.push_back(&eJeuFini);

	// Tant qu'on se trouve sur un �cran
	while(ecranActuel >= 0)
	{
		// On appel la fonction run qui boucle dans cet �cran et qui renvoie l'�cran suivant � ecranActuel
		ecranActuel = vectorEcrans[ecranActuel]->run(fenetre, perso1, perso2, affichage, carteJeu, son);
	}

	return 0;
}
