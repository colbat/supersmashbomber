#include "EcranJeuFini.h"

/**
 * Méthode principale de l'écran
 *
 * @Param sf::RenderWindow &fenetre
 * @Param Personnage &perso1
 * @Param Personnage &perso2
 * @Param Affichage &affichage
 * @Param Carte &carteJeu
 * @Son &son
 *
 * @Return int
 */
int EcranJeuFini::run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son)
{
	sf::Event monEvent;
	bool running = true;

	// On joue le son de victoire
	son.playWin();

	// On remet les scores des joueurs à zéro vu que le jeu est fini
	perso1.setScoreActuel(0);
	perso2.setScoreActuel(0);

	// Boucle du menu principal
	while(running)
	{
		while(fenetre.GetEvent(monEvent))
		{
			if (monEvent.Type == sf::Event::Closed)
            {
                son.stopMusic();
				// On quitte le jeu
                return (ECRAN_QUITTER);
            }
			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Escape))
            {
                son.stopMusic();
				// On quite le jeu
				return (ECRAN_MENU_PRINCIPAL);
			}
			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Return))
            {
                son.stopMusic();
				// On lance le jeu
				return (ECRAN_MENU_PRINCIPAL);
			}
		}
		fenetre.Clear();
		affichage.displayFond(fenetre);
		affichage.displayMap(fenetre);
		// On affiches les messages de fin de partie
		if(perso1.isVainqueurFinal()) affichage.displayFinJeu(fenetre, "1", 100, 250);
		else if(perso2.isVainqueurFinal()) affichage.displayFinJeu(fenetre, "2", 100, 250);

        affichage.displayPersoFini(&perso1, fenetre);
        affichage.displayPersoFini(&perso2, fenetre);
		// On affiche les scores
		affichage.displayScore(fenetre,perso1,90);
        affichage.displayScore(fenetre,perso2,400);
		affichage.displayAvatar(fenetre);
		// On affiche le contenu de l'écran
		fenetre.Display();
	}
	// Normalement on atteint jamais cet endroit, si jamais ça arrive on quitte le jeu.
	return (ECRAN_QUITTER);
}
