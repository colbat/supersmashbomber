#include "Personnage.h"
/* /!\ Ne pas changer l'ordre des define de direction /!\ */
#define BAS		0
#define DROITE	1
#define HAUT		2
#define GAUCHE	3

#define HITBOX_GAUCHE 5
#define HITBOX_HAUT 1
#define HITBOX_DROITE 35
#define HITBOX_BAS 39

#define HAUTEUR_FENETRE 740
#define LARGEUR_FENETRE 740
#define DECALAGE_CARTE 70

#define VITESSE_DEPLACEMENT 150

/**
* Constructeur de Personnage par défaut
*/
Personnage::Personnage()
{
}

/**
* Constructeur de Personnage
* Prend en paramètre un pointeur vers Affichage ( pour le lien ) et les 4 touches de direction.
*/
Personnage::Personnage(Carte *ptr_carte, int caseDepartX, int caseDepartY, sf::Key::Code toucheHaut, sf::Key::Code toucheDroite, sf::Key::Code toucheBas, sf::Key::Code toucheGauche, sf::Key::Code toucheBombe, int puissanceBombe, float tempsAttenteBombes)
: carte(ptr_carte), caseDepartX(caseDepartX), caseDepartY(caseDepartY), toucheHaut(toucheHaut), toucheDroite(toucheDroite), toucheBas(toucheBas), toucheGauche(toucheGauche), toucheBombe(toucheBombe), puissanceBombe(puissanceBombe), tempsAttenteBombes(tempsAttenteBombes)
{
	// Theme par défaut
	themePersonnage = "zelda";
	// On définit la case de départ du personnage
	spritePersonnage.SetPosition(caseDepartX*40 + DECALAGE_CARTE, caseDepartY*40 + DECALAGE_CARTE);
	// On définit la direction de départ du personnage
	directionPersonnage = DROITE;
	// 3 manches gagnantes par défaut pour remporté la partie
	nombreManchesGagnantes = 3;
	// Score par défaut à zero
	scoreActuel = 0;
	// Index de l'animation pour prendre le bon sprite en rapport avec la direction spécifiée
	indexPremierSpriteAnim = directionPersonnage * 3;
	// Personnage non actif par défaut ( il n'est pas sur le terrain )
	personnageActif = false;
	// Aucune bombe posée au debut
	bombePosee = false;
	// Le personnage n'est pas sur une bombe
	personnageSurBombe = false;
	// Premier sprite de l'animation, le personnage ne bouge pas quand il apparaît
	phaseDeplacement = 0;
	// On définit la puissance de la bombe
	puissanceBombe = 1;
}
/**
 * @Return void
 *
 */
void Personnage::initPersonnage()
{
	// Le personnage est en vie
	personnageEnVie = true;
	// On définit la case de départ du personnage
	spritePersonnage.SetPosition(caseDepartX*40 + DECALAGE_CARTE, caseDepartY*40 + DECALAGE_CARTE);
	// On définit la direction de départ du personnage
	directionPersonnage = DROITE;
	// On définit sa vitesse de déplacement
	vitesseDeplacement = VITESSE_DEPLACEMENT;
	// On définit la puissance de la bombe
	puissanceBombe = 1;
	// temps d'attente par default
	tempsAttenteBombes = 3;

}

/**
 * Capture des évenement et deplacement du personnage
 *
 * @Param const sf::Input &input
 * @Param sf::RenderWindow &fenetre
 *
 * @Return void
 */
void Personnage::controlerPersonnage(const sf::Input &input, sf::RenderWindow &fenetre)
{
    // Appel de la méthode de detection des collisions
	detectionCollision(fenetre);

	// Récupère le temps écouler pour afficher une frame
	float tempsEcoule = fenetre.GetFrameTime();

	// Si la touche haut est pressée et que les autre ne le sont pas ( le personnage reste sur place si on appuie sur 2 directions différentes en même temps )
	if ( (input.IsKeyDown(toucheHaut)) && (!input.IsKeyDown(toucheBas)) && (!input.IsKeyDown(toucheDroite)) && (!input.IsKeyDown(toucheGauche)) )
	{
		directionPersonnage = HAUT;
		// On initialise l'index du premier sprite affiché en fonction de la direction du perso et du nombre de sprite par direction.
		indexPremierSpriteAnim = directionPersonnage*3;

		// Au premier passage dans la boucle
		if(nouvelleDirection == true)
		{
			// On initialise la phase de déplacement actuelle directement au premier sprite de l'anim
			phaseDeplacement = indexPremierSpriteAnim;
			// Bool à false pour ne plus repasser dans ce 'if' quand la touche de déplacement restera appuyée.
			nouvelleDirection = false;
		}
		// On anime notre personnage.
		animationDeplacement();
		// On fait bouger le sprite de notre personnage en fonction du temps écoulé et de sa vitesse.
		spritePersonnage.Move(0, -vitesseDeplacement * tempsEcoule);
	}
	else if( (input.IsKeyDown(toucheBas)) && (!input.IsKeyDown(toucheHaut)) && (!input.IsKeyDown(toucheDroite)) && (!input.IsKeyDown(toucheGauche)) )
	{
		directionPersonnage = BAS;
		indexPremierSpriteAnim = directionPersonnage*3;

		if(nouvelleDirection == true)
		{
			phaseDeplacement = indexPremierSpriteAnim;
			nouvelleDirection = false;
		}
		animationDeplacement();

		spritePersonnage.Move(0, +vitesseDeplacement * tempsEcoule);
	}
	else if( (input.IsKeyDown(toucheDroite)) && (!input.IsKeyDown(toucheBas)) && (!input.IsKeyDown(toucheHaut)) && (!input.IsKeyDown(toucheGauche)) )
	{
		directionPersonnage = DROITE;
		indexPremierSpriteAnim = directionPersonnage*3;

		if(nouvelleDirection == true)
		{
			phaseDeplacement = indexPremierSpriteAnim;
			nouvelleDirection = false;
		}
		animationDeplacement();

		spritePersonnage.Move(vitesseDeplacement * tempsEcoule, 0);
	}
	else if( (input.IsKeyDown(toucheGauche)) && (!input.IsKeyDown(toucheBas)) && (!input.IsKeyDown(toucheDroite)) && (!input.IsKeyDown(toucheHaut)) )
	{
		directionPersonnage = GAUCHE;
		indexPremierSpriteAnim = directionPersonnage*3;

		if(nouvelleDirection == true)
		{
			phaseDeplacement = indexPremierSpriteAnim;
			nouvelleDirection = false;
		}
		animationDeplacement();

		spritePersonnage.Move(-vitesseDeplacement * tempsEcoule, 0);
	}
	// Si la touche de direction est relachee
	else
	{
		// Bool à true pour repasse dans le premier 'if' afin de prendre en compte le nouveau sprite de début en fonction de la direction
		nouvelleDirection = true;
		// On remet la phase de déplacement au premier sprite de l'anim
		phaseDeplacement = indexPremierSpriteAnim;
	}


	// Si on appuye sur la touche pour poser une bombe
	if(input.IsKeyDown(toucheBombe) && timerTouche.GetElapsedTime() > tempsAttenteBombes )
	{
        timerTouche.Reset();
        // Appel de la méthode pour poser une bombe
        poserBombe();
    }



}


/**
* Méthode pour la gestion des collisions
*
* @Param sf::RenderWindow &fenetre
*
* @Return void
*/
void Personnage::detectionCollision(sf::RenderWindow &fenetre)
{
	// On récupère dans quelle cases se trouvent les quatres coins du sprite
	caseCoinBasGauche = carte->getTableauCarte((int)((spritePersonnage.GetPosition().y + HITBOX_BAS - DECALAGE_CARTE) / 40), (int)((spritePersonnage.GetPosition().x + HITBOX_GAUCHE - DECALAGE_CARTE) / 40));
	caseCoinBasDroit = carte->getTableauCarte((int)((spritePersonnage.GetPosition().y + HITBOX_BAS - DECALAGE_CARTE) / 40), (int)((spritePersonnage.GetPosition().x + HITBOX_DROITE - DECALAGE_CARTE) / 40));
	caseCoinHautGauche = carte->getTableauCarte((int)((spritePersonnage.GetPosition().y + HITBOX_HAUT - DECALAGE_CARTE) / 40), (int)((spritePersonnage.GetPosition().x + HITBOX_GAUCHE - DECALAGE_CARTE) / 40));
	caseCoinHautDroit = carte->getTableauCarte((int)((spritePersonnage.GetPosition().y + HITBOX_HAUT - DECALAGE_CARTE) / 40), (int)((spritePersonnage.GetPosition().x + HITBOX_DROITE - DECALAGE_CARTE) / 40));

	if((caseCoinBasGauche != BOMBE) && (caseCoinBasDroit != BOMBE) && (caseCoinHautGauche != BOMBE) && (caseCoinHautDroit != BOMBE))
		personnageSurBombe = false;

	if((caseCoinBasGauche == EXPLOSION) || (caseCoinBasDroit == EXPLOSION) || (caseCoinHautGauche == EXPLOSION) || (caseCoinHautDroit == EXPLOSION))
	{
		personnageEnVie = false;
    }

	switch(directionPersonnage)
	{
		case BAS:
			// Si le personnage se retrouve contre le bord en bas
			if(spritePersonnage.GetPosition().y >= HAUTEUR_FENETRE - DECALAGE_CARTE - HITBOX_BAS)
			{
				// Si il dépasse ce bord, on remet le sprite contre le bord
				spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, HAUTEUR_FENETRE - DECALAGE_CARTE - 40);
			}
			else if(personnageSurBombe)
			{
				// Si un coin gauche ou un coin droit se trouve dans une case MUR, CAISSE
                if(((caseCoinBasGauche == MUR) || (caseCoinBasDroit == MUR)) ||
                ((caseCoinBasGauche == CAISSE) || (caseCoinBasDroit == CAISSE)))
				{
					// On calcule la position Y en pixel de cette case
					caseCollisionY = (int)(((spritePersonnage.GetPosition().y + 40 - 1) / 40)*40) - 1;
					// On remet le sprite contre cette case
					spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, caseCollisionY - 40 + 1);

					/* Affinage des collisions pour se déplacer plus facilement */
					// Si le coin coin gauche du sprite est sur une case "bloquante" et que le coin droit est sur une case vide
					if(affinageCollision(caseCoinBasGauche,caseCoinBasDroit))
					{
						// On calcule la position X en pixel de cette case
						caseCollisionX = ((int)((spritePersonnage.GetPosition().x + 40) / 40) * 40);
						// et tant qu'on a pas dépassé cette case, on fait bouger le personnage dans la bonne direction afin qu'il n'y ai plus blocage
						spritePersonnage.Move((vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}

					// Idem avec le coin droit du sprite sur une case "bloquante" et le coin gauche sur une case vide
					if(affinageCollision(caseCoinBasDroit,caseCoinBasGauche))
					{
						caseCollisionX = ((int)((spritePersonnage.GetPosition().x - 40) / 40) * 40);
                        spritePersonnage.Move((-vitesseDeplacement) * fenetre.GetFrameTime(), 0);

					}
				}
			}
			else
			{
                // Si un coin gauche ou un coin droit se trouve dans une case MUR, CAISSE
				if(((caseCoinBasGauche == MUR) || (caseCoinBasDroit == MUR)) ||
					((caseCoinBasGauche == CAISSE) || (caseCoinBasDroit == CAISSE)) ||
					((caseCoinBasGauche == BOMBE) || (caseCoinBasDroit == BOMBE)))
				{
					// On calcule la position Y en pixel de cette case
					caseCollisionY = (int)(((spritePersonnage.GetPosition().y + 40 - 1) / 40)*40) - 1;
					// On remet le sprite contre cette case
					spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, caseCollisionY - 40 + 1);

					/* Affinage des collisions pour se déplacer plus facilement */
					// Si le coin coin gauche du sprite est sur une case "bloquante" et que le coin droit est sur une case vide
					if (affinageCollision(caseCoinBasGauche, caseCoinBasDroit))
					{
						// On calcule la position X en pixel de cette case
						caseCollisionX = ((int)((spritePersonnage.GetPosition().x + 40) / 40) * 40);
						// et tant qu'on a pas dépassé cette case, on fait bouger le personnage dans la bonne direction afin qu'il n'y ai plus blocage
						spritePersonnage.Move((vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}

					// Idem avec le coin droit du sprite sur une case "bloquante" et le coin gauche sur une case vide
					if(affinageCollision(caseCoinBasDroit, caseCoinBasGauche))
					{
						caseCollisionX = ((int)((spritePersonnage.GetPosition().x - 40) / 40) * 40);
						spritePersonnage.Move((-vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}
				}
			}
			break;

		case DROITE:
			// Si dans ce cas le personnage se retrouve contre le bord
			if(spritePersonnage.GetPosition().x >= LARGEUR_FENETRE - DECALAGE_CARTE - HITBOX_DROITE)
			{
				spritePersonnage.SetPosition(LARGEUR_FENETRE - 40 + 4 - DECALAGE_CARTE, spritePersonnage.GetPosition().y);
			}
			else if(personnageSurBombe)
			{
				if(((caseCoinHautDroit == MUR) || (caseCoinBasDroit == MUR)) ||
				    ((caseCoinHautDroit == CAISSE) || (caseCoinBasDroit == CAISSE)))
				{
					caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 40 - 1) / 40)*40) - 1;
					spritePersonnage.SetPosition(caseCollisionX - 40 + 1, spritePersonnage.GetPosition().y);

					if( affinageCollision(caseCoinHautDroit,caseCoinBasDroit))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y + 40 + 1) / 40) * 40) + 1;
						spritePersonnage.Move(0, (vitesseDeplacement) * fenetre.GetFrameTime());
					}

					if( affinageCollision(caseCoinBasDroit,caseCoinHautDroit))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y - 40 - 1) / 40) * 40) + 1;
                        spritePersonnage.Move(0, (-vitesseDeplacement) * fenetre.GetFrameTime());
					}
				}
			}
			else
			{
				if(((caseCoinHautDroit == MUR) || (caseCoinBasDroit == MUR)) ||
				    ((caseCoinHautDroit == CAISSE) || (caseCoinBasDroit == CAISSE)) ||
					((caseCoinHautDroit == BOMBE) || (caseCoinBasDroit == BOMBE)))
				{
					caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 40 - 1) / 40)*40) - 1;
					spritePersonnage.SetPosition(caseCollisionX - 40 + 1, spritePersonnage.GetPosition().y);

					if( affinageCollision(caseCoinHautDroit,caseCoinBasDroit))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y + 40 + 1) / 40) * 40) + 1;
						spritePersonnage.Move(0, (vitesseDeplacement) * fenetre.GetFrameTime());
					}

					if( affinageCollision(caseCoinBasDroit,caseCoinHautDroit))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y - 40 - 1) / 40) * 40) + 1;
                        spritePersonnage.Move(0, (-vitesseDeplacement) * fenetre.GetFrameTime());
					}
				}

			}
			break;

		case HAUT:
			// Si le personnage se retrouve contre le bord en haut
			if(spritePersonnage.GetPosition().y <= DECALAGE_CARTE)
			{
				spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, DECALAGE_CARTE);
			}
			else if(personnageSurBombe)
			{
				if(((caseCoinHautGauche == MUR) || (caseCoinHautDroit == MUR)) ||
				    ((caseCoinHautGauche == CAISSE) || (caseCoinHautDroit == CAISSE)))
				{
					caseCollisionY = (int)(((spritePersonnage.GetPosition().y + 1) / 40)*40) + 2;
					spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, caseCollisionY - 1);

					if(affinageCollision(caseCoinHautGauche, caseCoinHautDroit))
					{
						caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 40) / 40)*40);
						spritePersonnage.Move((vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}

                    if(affinageCollision(caseCoinHautDroit, caseCoinHautGauche))
                    {
						caseCollisionX = (int)(((spritePersonnage.GetPosition().x - 40) / 40)*40);
                        spritePersonnage.Move((-vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}
				}
			}
			else
			{
				if(((caseCoinHautGauche == MUR) || (caseCoinHautDroit == MUR)) ||
				    ((caseCoinHautGauche == CAISSE) || (caseCoinHautDroit == CAISSE)) ||
					((caseCoinHautGauche == BOMBE) || (caseCoinHautDroit == BOMBE)))
				{
					caseCollisionY = (int)(((spritePersonnage.GetPosition().y + 1) / 40)*40) + 2;
					spritePersonnage.SetPosition(spritePersonnage.GetPosition().x, caseCollisionY - 1);

					if(affinageCollision(caseCoinHautGauche, caseCoinHautDroit))
					{
						caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 40) / 40)*40);
						spritePersonnage.Move((vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}

                    if(affinageCollision(caseCoinHautDroit, caseCoinHautGauche))
                    {
						caseCollisionX = (int)(((spritePersonnage.GetPosition().x - 40) / 40)*40);
                        spritePersonnage.Move((-vitesseDeplacement) * fenetre.GetFrameTime(), 0);
					}
				}
			}
			break;

		case GAUCHE:
			// Si dans ce cas le personnage se retrouve contre le bord
			if(spritePersonnage.GetPosition().x <= DECALAGE_CARTE)
			{
				spritePersonnage.SetPosition(DECALAGE_CARTE, spritePersonnage.GetPosition().y);
			}
			else if(personnageSurBombe)
			{
				if(((caseCoinHautGauche == MUR) || (caseCoinBasGauche == MUR)) ||
				    ((caseCoinHautGauche == CAISSE) || (caseCoinBasGauche == CAISSE)))
				{
					caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 1) / 40)*40) + 2;
					spritePersonnage.SetPosition(caseCollisionX - 1, spritePersonnage.GetPosition().y);

					if(affinageCollision(caseCoinHautGauche,caseCoinBasGauche))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y + 40 ) / 40) * 40);
						spritePersonnage.Move(0, (vitesseDeplacement) * fenetre.GetFrameTime());
					}

                    if(affinageCollision(caseCoinBasGauche,caseCoinHautGauche))
                    {
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y - 40) / 40) * 40);
                        spritePersonnage.Move(0, (-vitesseDeplacement) * fenetre.GetFrameTime());
					}
				}
			}
			else
			{
				if(((caseCoinHautGauche == MUR) || (caseCoinBasGauche == MUR)) ||
				    ((caseCoinHautGauche == CAISSE) || (caseCoinBasGauche == CAISSE)) ||
					((caseCoinHautGauche == BOMBE) || (caseCoinBasGauche == BOMBE)))
				{
					caseCollisionX = (int)(((spritePersonnage.GetPosition().x + 1) / 40)*40) + 2;
					spritePersonnage.SetPosition(caseCollisionX - 1, spritePersonnage.GetPosition().y);

                    if(affinageCollision(caseCoinHautGauche,caseCoinBasGauche))
					{
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y + 40 ) / 40) * 40);
						spritePersonnage.Move(0, (vitesseDeplacement) * fenetre.GetFrameTime());
					}

                    if(affinageCollision(caseCoinBasGauche,caseCoinHautGauche))
                    {
						caseCollisionY = ((int)((spritePersonnage.GetPosition().y - 40) / 40) * 40);
                        spritePersonnage.Move(0, (-vitesseDeplacement) * fenetre.GetFrameTime());
					}

				}
			}
			break;
		default:
			//...
			break;
	}
}

/**
* Méthode pour gérer l'animation du personnage quand il se déplace
*
* @Return void
*/
void Personnage::animationDeplacement()
{
    /* Temps que met le personnage pour changer de phase d'animation
	    Plus c'est petit et plus le personnage aura l'impression de courrir */
	float tempsEntrePhase = 0.25f;

	// On récupère le dernier sprite de l'animation à partir du premier auquel on ajoute 2 car il y a 3 sprite par direction.
	indexDernierSpriteAnim = indexPremierSpriteAnim + 2;

	// Toute les 0,25 sec
	if(timerAnimation.GetElapsedTime() >= tempsEntrePhase)
	{
		// Si la phase de deplacement est inférieur au dernier sprite.
		if(phaseDeplacement < indexDernierSpriteAnim)
			// On incrément la phase de déplacement.
			phaseDeplacement++;
		else
			// Et quand on arrive au dernier sprite, on remet la phase de déplacement au premier.
			phaseDeplacement = indexPremierSpriteAnim;

		// On reset le chrono
		timerAnimation.Reset();
	}

}

/**
* Méthode pour poser une bombe
*
* @Return void
*/
void Personnage::poserBombe()
{
    bombePosee = true;
	personnageSurBombe = true;
}

/**
 * Méthode pour affiner les collisions
 *
 * @Param int coinX
 * @Param int coinY
 *
 * @Return bool
 */
bool Personnage::affinageCollision(int coinX, int coinY)
{
    if(coinX == MUR || coinX == CAISSE && coinY == VIDE || coinY == HERBE
    || coinY == PUISSANCE || coinY == NOMBREBOMBE || coinY == VITESSEMOISNS || coinY == VITESSEPLUS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Méthode pour ramasser les bonus au sol
 * @Param Carte *ptr_carte pointeur
 * @Param Son *ptr_son pointeur
 */
void Personnage::ramasserBonus(Carte *ptr_carte, Son *ptr_son)
{
    int positionX = int((spritePersonnage.GetPosition().x +20)/40 - (70.f / 40.f));
	int positionY = int((spritePersonnage.GetPosition().y +20)/40 - (70.f / 40.f));
    // Dans le cas d'un bonus de puissance, on augmente celle ci
    if (ptr_carte->getTableauCarte(positionY,positionX) == PUISSANCE)
    {
        puissanceBombe++;
        ptr_carte->setTableauCarte(positionY, positionX, 0);
        ptr_son->playBonus();
    }
    // Dans le cas d'un bonus de vitesse, on modifie les attributs du personnage
    else if (ptr_carte->getTableauCarte(positionY,positionX) == VITESSEPLUS)
    {
		if(vitesseDeplacement <= 400)
			vitesseDeplacement += 50;

        ptr_carte->setTableauCarte(positionY, positionX, 0);
        ptr_son->playBonus();
    }
    // Dans le cas d'un bonus de vitesse, on modifie les attributs du personnage
    else if (ptr_carte->getTableauCarte(positionY,positionX) == VITESSEMOISNS)
    {
		if(vitesseDeplacement <= 100)
			vitesseDeplacement = 100;
		else
			vitesseDeplacement -= 50;

        ptr_carte->setTableauCarte(positionY, positionX, 0);
        ptr_son->playBonus();
    }
    else if (ptr_carte->getTableauCarte(positionY,positionX) == NOMBREBOMBE)
    {
        if (tempsAttenteBombes > 1) {
        tempsAttenteBombes = tempsAttenteBombes - 1;
        ptr_carte->setTableauCarte(positionY, positionX, 0);
        ptr_son->playBonus();
        } else {
        tempsAttenteBombes = 0.5;
        ptr_carte->setTableauCarte(positionY, positionX, 0);
        ptr_son->playBonus();
        }


    }
}


/* --- Getters --- */

/** Sprite du personnage*/
sf::Sprite& Personnage::getSpritePersonnage()
{
	return spritePersonnage;
}

/** Direction du personnage*/
int Personnage::getDirectionPersonnage() const
{
	return directionPersonnage;
}

/** Phase de déplacement du personnage */
int Personnage::getPhaseDeplacement() const
{
	return phaseDeplacement;
}

int Personnage::getPuissanceBombes()
{
    return puissanceBombe;
}

int Personnage::getVitesseDeplacement()
{
    return vitesseDeplacement;
}

/** Personnage vivant ou non*/
bool Personnage::isVivant() const
{
	return personnageEnVie;
}

/** Personnage actif ou non*/
bool Personnage::isActif() const
{
	return personnageActif;
}

/** Pour debugage ... */
int Personnage::getDernierSpriteAnim()
{
	return indexDernierSpriteAnim;
}

/** Bombe posee ou non */
bool Personnage::isBombePosee()
{
    return bombePosee;
}

/** Retourne le theme de personnage */
std::string Personnage::getThemePersonnage()
{
	return themePersonnage;
}

/** Retourne le nombre de manche gagnante */
int Personnage::getNombreDeManchesGagnantes()
{
	return nombreManchesGagnantes;
}

/** Retourne le score du personnage */
int Personnage::getScoreActuel()
{
	return scoreActuel;
}

/** Retourne le nombre de bombe possible */
int Personnage::getTempsAttenteBombes()
{
  return tempsAttenteBombes;
}

/** Retourne si le personnage à remporté le jeu ou non */
bool Personnage::isVainqueurFinal()
{
	return personnageVainqueurFinal;
}

/* --- Setters --- */

/** Definir si une bombe à été posée par le personnage*/
void Personnage::setBombePosee(bool posee)
{
	 bombePosee = posee;
}
/** Définir si le perso est vivant ou mort */
void Personnage::setVivant(bool vivant)
{
    this->personnageEnVie = vivant;
}
/** Définir si le personnage est actif ou non */
void Personnage::setActif(bool actif)
{
	personnageActif = actif;
}

/** Theme du personnage */
void Personnage::setThemePersonnage(std::string pTheme)
{
	themePersonnage = pTheme;
}

/** Nombre de manche gagnante */
void Personnage::setNombreDeManchesGagnantes(int pNbManche)
{
	nombreManchesGagnantes = pNbManche;
}

/** Score du personnage */
void Personnage::setScoreActuel(int pScore)
{
	scoreActuel = pScore;
}

/** Personnage vainqueur ou non */
void Personnage::setVainqueurFinal(bool vainqueur)
{
	personnageVainqueurFinal = vainqueur;
}


