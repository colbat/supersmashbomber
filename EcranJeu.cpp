#include "EcranJeu.h"
using namespace std;

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
int EcranJeu::run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son)
{
	sf::Event monEvent;
	bool running = true;

	/* --- INITIALISATION DU JEU --- */
    // On choisi quel personnage rendre actif (perso2 par default à false)
	perso1.setActif(true);
	perso2.setActif(true);
	// Les deux personnages sont vivants
	perso1.setVivant(true);
	perso2.setVivant(true);
    // Initialisation de la carte grace au fichier de niveau
	carteJeu.initCarte("levels/niveau1.lvl");
	// Initialisation aléatoire des bonus (indiquer la fréquence souhaitée de 0 à 100)
	carteJeu.initBonus(99);
	// On charge les images de la carte
	affichage.chargerThemeCarte();
    // On charge les images des personnages
	affichage.chargerThemePersonnage(perso1, perso2);
	// On charge les sons en fonction du theme de la carte
	son.chargerSons(affichage.getThemeCarte());
	// On charge la police de caractère pour l'affichage des scores
	affichage.chargerPoliceCaractere("GameCube.ttf", 30);
    // On lance le thème musical
    son.playMusic();
	// Initialisation des personnages
	perso1.initPersonnage();
	perso2.initPersonnage();
	// Initialisation du BombesManager
	BombesManager manageBombe;
    /* --- FIN INITIALISATION DU JEU --- */

    /* --- BOUCLE PRINCIPALE DU JEU ---*/
	while(running)
	{
		// Boucle des évennements
		while(fenetre.GetEvent(monEvent))
		{
			if (monEvent.Type == sf::Event::Closed)
            {
                son.stopMusic();
               return (ECRAN_MENU_PRINCIPAL); // On retourne à l'écran du menu principal
            }
			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Escape))
            {
                son.stopMusic();
                return (ECRAN_MENU_PRINCIPAL);// On retourne à l'écran du menu principal
			}
			if ((monEvent.Type == sf::Event::KeyPressed) && (monEvent.Key.Code == sf::Key::Back))
            {
                son.stopMusic();
                return (ECRAN_MENU_PRINCIPAL);// On retourne à l'écran du menu principal
			}
		}
		// On efface l'écran
		fenetre.Clear();
		// On affiche le fond
		affichage.displayFond(fenetre);
		// On affiche la map
		affichage.displayMap(fenetre);
        // Tant que les deux personnages sont vivants
		if(perso1.isVivant() && perso2.isVivant())
		{
			// On récupère les évenements des joueurs
			if(perso1.isActif()) perso1.controlerPersonnage(fenetre.GetInput(), fenetre);
			if(perso2.isActif()) perso2.controlerPersonnage(fenetre.GetInput(), fenetre);
			// On traite les bombes
			if(perso1.isActif()) manageBombe.traitementBombe(&perso1, &carteJeu, &son);
			if(perso2.isActif()) manageBombe.traitementBombe(&perso2, &carteJeu, &son);
			// On traite les bonus
			if(perso1.isActif()) perso1.ramasserBonus(&carteJeu, &son);
			if(perso2.isActif()) perso2.ramasserBonus(&carteJeu, &son);
			// On affiches les personnages vivants
			if(perso1.isActif()) affichage.displayPerso(&perso1, fenetre);
			if(perso2.isActif()) affichage.displayPerso(&perso2, fenetre);
		}
		/* --- Test sur l'état des personnages --- */
		else if(perso1.isVivant() && !perso2.isVivant())
		{
			// On incrémente le score du perso1
			perso1.setScoreActuel(perso1.getScoreActuel() + 1);
			// Test si le perso1 à remporté le jeu
			if(perso1.getScoreActuel() < perso1.getNombreDeManchesGagnantes()) {
				return (ECRAN_MANCHE_FINIE);
			}
			else if(perso1.getScoreActuel() == perso1.getNombreDeManchesGagnantes()) {
				perso1.setVainqueurFinal(true);
				return (ECRAN_JEU_FINI);
			}
		}
		else if(!perso1.isVivant() && perso2.isVivant())
		{
			// On incrémente le score du perso2
			perso2.setScoreActuel(perso2.getScoreActuel() + 1);
			// Test si le perso2 à remporté le jeu ou juste cette manche
			if(perso2.getScoreActuel() < perso2.getNombreDeManchesGagnantes()) {
				return (ECRAN_MANCHE_FINIE);
			}
			else if(perso2.getScoreActuel() == perso2.getNombreDeManchesGagnantes()) {
				perso2.setVainqueurFinal(true);
				return (ECRAN_JEU_FINI);
			}
		}
		else if(!perso1.isVivant() && !perso2.isVivant())
		{
            return (ECRAN_MANCHE_FINIE);
		}
		// On affiche les scores
		affichage.displayScore(fenetre,perso1,90);
        affichage.displayScore(fenetre,perso2,400);
		affichage.displayAvatar(fenetre);
        // On affiche le contenu de la fenetre
        fenetre.Display();
	}
	/* --- FIN BOUCLE PRINCIPALE --- */
	return (ECRAN_QUITTER);
}

