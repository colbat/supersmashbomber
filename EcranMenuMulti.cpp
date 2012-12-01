#include "EcranMenuMulti.h"

#define TAILLEFLECHE 40
#define TAILLEIMAGEPERSO 90
#define TAILLETILEPERSO 180
#define TAILLEIMAGEMAP 120
#define TAILLETILEMAP 240
#define TAILLEIMAGEMANCHES 45
#define TAILLETILEMANCHES 405

/**
 *Constructeur par défaut
 */
EcranMenuMulti::EcranMenuMulti()
{
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
int EcranMenuMulti::run(sf::RenderWindow &fenetre, Personnage &perso1, Personnage &perso2, Affichage &affichage, Carte &carteJeu, Son &son)
{
	sf::Event monEvent;
	bool running = true;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

    //Chargement de l'image de fond du menu multijoueur
    if (!ImageMulti.LoadFromFile("tilesets/MenuMulti.png"))
		std::cout << "Erreur chargement image du menu multi" << std::endl;

    //Chargement du tile pour le choix des personnages
    if (!ImagePerso.LoadFromFile("tilesets/Tile_perso.jpg"))
		std::cout << "Erreur chargement image du menu multi (tile perso)" << std::endl;

    //Chargement du tile pour le choix de la map
    if (!ImageMap.LoadFromFile("tilesets/Tile_Map.png"))
		std::cout << "Erreur chargement image du menu multi (tile map)" << std::endl;

    //Chargement de l'image flèche droite
    if (!ImageFlecheDroite.LoadFromFile("tilesets/FlecheDroite.png"))
		std::cout << "Erreur chargement image du menu multi (fleche droite) '" << std::endl;

    //Chargement de l'image flèche droite
    if (!ImageFlecheGauche.LoadFromFile("tilesets/FlecheGauche.png"))
		std::cout << "Erreur chargement image du menu multi (fleche gauche)" << std::endl;

    //Chargement de l'image pour le nombre de manches gagnantes
    if (!ImageNombreManches.LoadFromFile("tilesets/Tile_NombreManches.png"))
		std::cout << "Erreur chargement image du menu multi (tile nombre de manches)" << std::endl;


    //Chargement des images dans les sprites
    SpriteMulti.SetImage(ImageMulti);
    SpriteFlecheDroite1.SetImage(ImageFlecheDroite);
    SpriteFlecheDroite2.SetImage(ImageFlecheDroite);
    SpriteFlecheDroite3.SetImage(ImageFlecheDroite);
    SpriteFlecheDroite4.SetImage(ImageFlecheDroite);

    //Position des différents sprites
    SpriteFlecheDroite1.SetPosition(230, 450);
    SpriteFlecheDroite2.SetPosition(230, 620);
    SpriteFlecheDroite3.SetPosition(630, 390);
    SpriteFlecheDroite4.SetPosition(590, 587);

    SpriteFlecheGauche1.SetImage(ImageFlecheGauche);
    SpriteFlecheGauche2.SetImage(ImageFlecheGauche);
    SpriteFlecheGauche3.SetImage(ImageFlecheGauche);
    SpriteFlecheGauche4.SetImage(ImageFlecheGauche);
    SpriteFlecheGauche5.SetImage(ImageFlecheGauche);
    SpriteFlecheGauche1.SetPosition(50, 450);
    SpriteFlecheGauche2.SetPosition(50, 620);
    SpriteFlecheGauche3.SetPosition(420, 390);
    SpriteFlecheGauche4.SetPosition(5, 695);
    SpriteFlecheGauche5.SetPosition(455, 587);

    SpritePerso1.SetImage(ImagePerso);
    SpritePerso1.SetSubRect(sf::IntRect(0, 0, TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
    SpritePerso2.SetImage(ImagePerso);
    SpritePerso2.SetSubRect(sf::IntRect(0, 0, TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
    SpriteMap.SetImage(ImageMap);
    SpriteMap.SetSubRect(sf::IntRect(0, 0, TAILLEIMAGEMAP, TAILLEIMAGEMAP));
    SpriteNombreManches.SetImage(ImageNombreManches);
    SpriteNombreManches.SetSubRect(sf::IntRect(0, 0, TAILLEIMAGEMANCHES, TAILLEIMAGEMANCHES));
    SpritePerso1.SetPosition(115, 425);
    SpritePerso2.SetPosition(115, 595);
    SpriteMap.SetPosition(485, 350);
    SpriteNombreManches.SetPosition(520, 585);


    while(running)
	{
	    //Tant que la fenêtre contient des évènements
        while(fenetre.GetEvent(monEvent))
		{
			if (monEvent.Type == sf::Event::Closed)
				return (ECRAN_QUITTER); // On quitte le jeu

            if((monEvent.Type == sf::Event::MouseButtonPressed) && (monEvent.MouseButton.Button == sf::Mouse::Left))
            {
                //Cas ou on clique sur la fleche précédant
                if(monEvent.MouseButton.X > SpriteFlecheGauche4.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheGauche4.GetPosition().x + TAILLEFLECHE)
                {
                    if(monEvent.MouseButton.Y > SpriteFlecheGauche4.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheGauche4.GetPosition().y + TAILLEFLECHE)
                    {
                        //On affiche le Menu Principal
                        return (ECRAN_MENU_PRINCIPAL);
                    }
                }
                if(monEvent.MouseButton.X > SpriteFlecheGauche1.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheGauche1.GetPosition().x + TAILLEFLECHE)
                {
                    //Cas ou on clique sur la fleche précédant pour le choix du Perso 1
                    if(monEvent.MouseButton.Y > SpriteFlecheGauche1.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheGauche1.GetPosition().y + TAILLEFLECHE)
                    {
                        i = i - TAILLEIMAGEPERSO;
                        if(i < 0)
                        {
                            i = TAILLETILEPERSO - TAILLEIMAGEPERSO;
                        }

                        SpritePerso1.SetSubRect(sf::IntRect(i, 0, i + TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
                    }
                    //Cas ou on clique sur la fleche précédant pour le choix du Perso 2
                    if(monEvent.MouseButton.Y > SpriteFlecheGauche2.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheGauche2.GetPosition().y + TAILLEFLECHE)
                    {
                        j = j - TAILLEIMAGEPERSO;
                        if(j < 0)
                        {
                            j = TAILLETILEPERSO - TAILLEIMAGEPERSO;
                        }
                        SpritePerso2.SetSubRect(sf::IntRect(j, 0, j + TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
                    }
                }

                if(monEvent.MouseButton.X > SpriteFlecheDroite1.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheDroite1.GetPosition().x + TAILLEFLECHE)
                {
                    //Cas ou on clique sur la fleche suivant pour le choix du Perso 1
                    if(monEvent.MouseButton.Y > SpriteFlecheDroite1.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheDroite1.GetPosition().y + TAILLEFLECHE)
                    {
                        i = i + TAILLEIMAGEPERSO;
                        if(i >= TAILLETILEPERSO)
                        {
                            i = 0;
                        }
                        SpritePerso1.SetSubRect(sf::IntRect(i, 0, i + TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
                    }
                    //Cas ou on clique sur la fleche suivant pour le choix du Perso 2
                    if(monEvent.MouseButton.Y > SpriteFlecheDroite2.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheDroite2.GetPosition().y + TAILLEFLECHE)
                    {
                        j = j + TAILLEIMAGEPERSO;
                        if(j >= TAILLETILEPERSO)
                        {
                            j = 0;
                        }
                        SpritePerso2.SetSubRect(sf::IntRect(j, 0, j + TAILLEIMAGEPERSO, TAILLEIMAGEPERSO));
                    }
                }

                if(monEvent.MouseButton.Y > SpriteFlecheDroite3.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheDroite3.GetPosition().y + TAILLEFLECHE)
                {
                    //Cas ou on clique sur la fleche précédant pour le choix de la map
                    if(monEvent.MouseButton.X > SpriteFlecheGauche3.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheGauche3.GetPosition().x + TAILLEFLECHE)
                    {
                        k = k - TAILLEIMAGEMAP;
                        if(k < 0)
                        {
                            k = TAILLETILEMAP - TAILLEIMAGEMAP;
                        }
                        SpriteMap.SetSubRect(sf::IntRect(k, 0, k + TAILLEIMAGEMAP, TAILLEIMAGEMAP));
                    }
                    //Cas ou on clique sur la fleche suivant pour le choix de la map
                    if(monEvent.MouseButton.X > SpriteFlecheDroite3.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheDroite3.GetPosition().x + TAILLEFLECHE)
                    {
                        k = k + TAILLEIMAGEMAP;
                        if(k >= TAILLETILEMAP)
                        {
                            k = 0;
                        }
                        SpriteMap.SetSubRect(sf::IntRect(k, 0, k + TAILLEIMAGEMAP, TAILLEIMAGEMAP));
                    }
                }


                if(monEvent.MouseButton.Y > SpriteFlecheDroite4.GetPosition().y && monEvent.MouseButton.Y < SpriteFlecheDroite4.GetPosition().y + TAILLEFLECHE)
                {
                    //Cas ou on clique sur la fleche précédant pour le choix du nombre de manches gagnantes
                    if(monEvent.MouseButton.X > SpriteFlecheGauche5.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheGauche5.GetPosition().x + TAILLEFLECHE)
                    {
                        l = l - TAILLEIMAGEMANCHES;
                        if(l < 0)
                        {
                            l = TAILLETILEMANCHES - TAILLEIMAGEMANCHES;
                        }
                        SpriteNombreManches.SetSubRect(sf::IntRect(l, 0, l + TAILLEIMAGEMANCHES, TAILLEIMAGEMANCHES));
                    }

                    //Cas ou on clique sur la fleche suivant pour le choix du nombre de manches gagnantes
                    if(monEvent.MouseButton.X > SpriteFlecheDroite4.GetPosition().x && monEvent.MouseButton.X < SpriteFlecheDroite4.GetPosition().x + TAILLEFLECHE)
                    {
                        l = l + TAILLEIMAGEMANCHES;
                        if(l >= TAILLETILEMANCHES)
                        {
                            l = 0;
                        }
                        SpriteNombreManches.SetSubRect(sf::IntRect(l, 0, l + TAILLEIMAGEMANCHES, TAILLEIMAGEMANCHES));
                    }
                }

                //Cas ou on clique sur Commencer
                if(monEvent.MouseButton.X > 530 && monEvent.MouseButton.X < 710)
                {
                    if(monEvent.MouseButton.Y > 660 && monEvent.MouseButton.Y < 710)
                        {
                            //Switch sur i pour savoir quel perso a choisi le joueur 1
                            switch(i)
                            {
                                case 0*TAILLEIMAGEPERSO:
                                joueur1 = "zelda";
                                break;

                                case 1*TAILLEIMAGEPERSO:
                                joueur1 = "mario";
                                break;

                            }

                            //Switch sur j pour savoir quel perso a choisi le joueur 2
                            switch(j)
                            {
                                case 0*TAILLEIMAGEPERSO:
                                joueur2 = "zelda";
                                break;

                                case 1*TAILLEIMAGEPERSO:
                                joueur2 = "mario";
                                break;

                            }

                            //Switch sur k pour savoir quel map ont choisi les joueurs
                            switch(k)
                            {
                                case 0*TAILLEIMAGEMAP:
                                map = "zelda";
                                break;

                                case 1*TAILLEIMAGEMAP:
                                map = "mario";
                                break;

                            }

                            //On initialise le nombre de parties gagnantes
							perso1.setNombreDeManchesGagnantes((int)(l / TAILLEIMAGEMANCHES) + 1);
							perso2.setNombreDeManchesGagnantes((int)(l / TAILLEIMAGEMANCHES) + 1);

							perso1.setThemePersonnage(joueur1);
                            perso2.setThemePersonnage(joueur2);
                            affichage.setThemeCarte(map);
                            return (ECRAN_JEU); // On rentre dans l'écran du jeu
                        }
                }
            }
		}

		fenetre.Clear();
		fenetre.Draw(SpriteMulti);

		fenetre.Draw(SpriteFlecheDroite1);
		fenetre.Draw(SpriteFlecheDroite2);
		fenetre.Draw(SpriteFlecheDroite3);
		fenetre.Draw(SpriteFlecheDroite4);
		fenetre.Draw(SpriteFlecheGauche1);
		fenetre.Draw(SpriteFlecheGauche2);
		fenetre.Draw(SpriteFlecheGauche3);
		fenetre.Draw(SpriteFlecheGauche4);
		fenetre.Draw(SpriteFlecheGauche5);

		fenetre.Draw(SpritePerso1);
		fenetre.Draw(SpritePerso2);
		fenetre.Draw(SpriteMap);
		fenetre.Draw(SpriteNombreManches);
		fenetre.Display();
	}
	return (ECRAN_QUITTER);
}

