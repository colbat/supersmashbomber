#include "EcranMancheFinie.h"

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
int EcranMancheFinie::run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son)
{
	sf::Event monEvent;
	bool running = true;

	// On joue le son de victoire
	son.playWin();

	// Boucle du menu principal
	while(running)
	{
		while(fenetre.GetEvent(monEvent))
		{
		    if (monEvent.Type == sf::Event::Closed)
		    {
		        //On stoppe la musique
                son.stopMusic();
				return (ECRAN_MENU_PRINCIPAL); // On quitte le jeu
		    }

			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Return))
            {
				// On relance le jeu à nouveau
				return (ECRAN_JEU);
			}
			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Escape))
            {
                son.stopMusic();
				// On relance le jeu à nouveau
				return (ECRAN_MENU_PRINCIPAL);
			}

		}
		// On affiche le contenu de l'écran
        fenetre.Clear();
        affichage.displayFond(fenetre);
        affichage.displayMap(fenetre);

		// On affiches les sprites de fin de manche
		if(perso1.isVivant() && !perso2.isVivant())
		{
			affichage.displayFinManche(fenetre, "1", 100, 250);
		}
		else if(perso2.isVivant() && !perso1.isVivant())
		{
			affichage.displayFinManche(fenetre, "2", 100, 250);
		}
		else if(!perso1.isVivant() && !perso2.isVivant())
		{
		    affichage.displayFinMancheEgal(fenetre, 100, 250);
        }

		affichage.displayPersoFini(&perso1, fenetre);
		affichage.displayPersoFini(&perso2, fenetre);

		// On affiche les scores
		affichage.displayScore(fenetre,perso1,90);
        affichage.displayScore(fenetre,perso2,400);
        // On affiche le contenu de la fenetre
		affichage.displayAvatar(fenetre);
		fenetre.Display();
	}
	// Normalement on atteint jamais cet endroit, si jamais ça arrive on quitte le jeu.
	return (ECRAN_QUITTER);
}
