#include "EcranMenu.h"

#define LONGUEURBOUTTON 200
#define LARGEURBOUTTON 60

/**
 *Constructeur par défaut
 */
EcranMenu::EcranMenu()
{
    //initialisation a false pour le clignotement des boutons
    unJoueur = false;
    multi = false;
    quitter = false;
}

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
int EcranMenu::run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son)
{
	sf::Event monEvent;
	bool running = true;

	if (!Image.LoadFromFile("tilesets/Menu.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageUnJoueur.LoadFromFile("tilesets/UnJoueur.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageMulti.LoadFromFile("tilesets/Multi.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageQuitter.LoadFromFile("tilesets/Quitter.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageUnJoueurJ.LoadFromFile("tilesets/UnJoueurJ.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageMultiJ.LoadFromFile("tilesets/MultiJ.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;

    if (!ImageQuitterJ.LoadFromFile("tilesets/QuitterJ.png"))
		std::cout << "Erreur chargement image menu..." << std::endl;



	Sprite.SetImage(Image);
	SpriteUnJoueur.SetImage(ImageUnJoueur);
    SpriteUnJoueur.SetPosition(270, 400);
    SpriteUnJoueurJ.SetImage(ImageUnJoueurJ);
    SpriteUnJoueurJ.SetPosition(270, 400);
    SpriteMulti.SetImage(ImageMulti);
    SpriteMulti.SetPosition(270, 500);
    SpriteMultiJ.SetImage(ImageMultiJ);
    SpriteMultiJ.SetPosition(270, 500);
    SpriteQuitter.SetImage(ImageQuitter);
    SpriteQuitter.SetPosition(270, 600);
    SpriteQuitterJ.SetImage(ImageQuitterJ);
    SpriteQuitterJ.SetPosition(270, 600);


	// Boucle du menu principal
	while(running)
	{
		while(fenetre.GetEvent(monEvent))
		{
			if (monEvent.Type == sf::Event::Closed)
			{
				return (ECRAN_QUITTER); // On quitte le jeu
			}

			if((monEvent.Type == sf::Event::MouseButtonPressed) && (monEvent.MouseButton.Button == sf::Mouse::Left))
            {
                if(monEvent.MouseButton.X > SpriteUnJoueur.GetPosition().x && monEvent.MouseButton.X < SpriteUnJoueur.GetPosition().x + LONGUEURBOUTTON)
                {
                    if(monEvent.MouseButton.Y > SpriteUnJoueur.GetPosition().y && monEvent.MouseButton.Y < SpriteUnJoueur.GetPosition().y + LARGEURBOUTTON)
					{
					}

                    if(monEvent.MouseButton.Y > SpriteMulti.GetPosition().y && monEvent.MouseButton.Y < SpriteMulti.GetPosition().y + LARGEURBOUTTON)
					{
						return (ECRAN_MENU_MULTI);
					}

					if(monEvent.MouseButton.Y > SpriteQuitter.GetPosition().y && monEvent.MouseButton.Y < SpriteQuitter.GetPosition().y + LARGEURBOUTTON)
					{
						return (ECRAN_QUITTER);
					}
                }
            }

            if(monEvent.Type == sf::Event::MouseMoved)
            {
                if(monEvent.MouseMove.X > SpriteUnJoueur.GetPosition().x && monEvent.MouseMove.X < SpriteUnJoueur.GetPosition().x + LONGUEURBOUTTON)
                {
                    if(monEvent.MouseMove.Y > SpriteUnJoueur.GetPosition().y && monEvent.MouseMove.Y < SpriteUnJoueur.GetPosition().y + LARGEURBOUTTON)
                    {
                        unJoueur = true;
					    multi = false;
					    quitter = false;
                    }

                    if(monEvent.MouseMove.Y > SpriteMulti.GetPosition().y && monEvent.MouseMove.Y < SpriteMulti.GetPosition().y + LARGEURBOUTTON)
                    {
                        unJoueur = false;
					    multi = true;
					    quitter = false;
                    }

                    if(monEvent.MouseMove.Y > SpriteQuitter.GetPosition().y && monEvent.MouseMove.Y < SpriteQuitter.GetPosition().y + LARGEURBOUTTON)
                    {
                        unJoueur = false;
					    multi = false;
					    quitter = true;
                    }
                }
                else
                    {
                        unJoueur = false;
                        multi = false;
                        quitter = false;
                    }
            }
		}
		// On efface l'écran
		fenetre.Clear();
		// On affiche le sprite de fond
		fenetre.Draw(Sprite);
		if(!unJoueur)
            fenetre.Draw(SpriteUnJoueur);

		else
            fenetre.Draw(SpriteUnJoueurJ);

        if(!multi)
            fenetre.Draw(SpriteMulti);

        else
           fenetre.Draw(SpriteMultiJ);

        if(!quitter)
            fenetre.Draw(SpriteQuitter);

        else
            fenetre.Draw(SpriteQuitterJ);

		// On affiche le contenu de la fenêtre
		fenetre.Display();
	}
	// Normalement on atteint jamais cet endroit, si jamais ça arrive on quitte le jeu.
	return (ECRAN_QUITTER);
}
