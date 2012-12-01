#include "BombesManager.h"


/**
 *
 * @param Personnage *ptr_personnage
 * @param Carte *ptr_carte
 * @param Son *ptr_son
 *
 * @return void
 */
void BombesManager::traitementBombe(Personnage *ptr_personnage, Carte *ptr_carte, Son *ptr_son)
{
        // Si une bombe � �t� pos�e lors de ce passage dans la boucle
		if(ptr_personnage->isBombePosee())
        {
            // On instancie un nouvel objet bombe
            Bombe bombe(ptr_carte);
            // On lui assigne les position du personnage (qui seront converties en case)
            bombe.position(ptr_personnage->getSpritePersonnage().GetPosition().x,ptr_personnage->getSpritePersonnage().GetPosition().y, ptr_personnage->getPuissanceBombes());
            bombe.poserBombe();
            // On envoit l'objet bombe dans la file
            qBombesExplosion.push(bombe);
            // On r�cuper l'instant t auquel la bombe � �t� pos�e et on lui ajoute 3 secondes
            tempsBombePosee = timer.GetElapsedTime() + 3.0f;

            // On envoit cette donn�e dans la file du timer
            timerBombeExplosion.push(tempsBombePosee);
            // On remet le bool�en � false pour �viter que la bombe soit pos�e au prochain tour de boucle
            ptr_personnage->setBombePosee(false);

        }
        tempsEcoule = timer.GetElapsedTime();

		// Si la file n'est pas vide
		if(!timerBombeExplosion.empty())
		{
			// Si le teamps �coul� est �gal au prochain temps contenu en sortie de file (explosion de la bombe)
			if ( tempsEcoule > timerBombeExplosion.front())
			{
				// On sort l'objet bombe cr�� il y � 3 seconde et on apelle sa m�thode explosion
				ptr_carte->explosion(qBombesExplosion.front().getPositionX(), qBombesExplosion.front().getPositionY(), qBombesExplosion.front().getForce(), true);
				//qBombesExplosion.front().explosionTest();
				timerBombeExplosion.front();
				ptr_son->playExplosion();



				qBombesFinExplosion.push(qBombesExplosion.front());
				qBombesExplosion.pop();
				timerBombeFinExplosion.push(timerBombeExplosion.front());
				timerBombeExplosion.pop();
			}
		}

		// Si la file n'est pas vide
		if(!timerBombeFinExplosion.empty())
		{
			// Si le teamps �coul� est �gal au prochain temps contenu en sortie de file (fin de l'explosion de la bombe)
			if ( tempsEcoule > timerBombeFinExplosion.front() + 0.25f)
			{
				ptr_carte->explosion(qBombesFinExplosion.front().getPositionX(), qBombesFinExplosion.front().getPositionY(), qBombesFinExplosion.front().getForce(), false);

				timerBombeFinExplosion.pop();

				if(!qBombesFinExplosion.empty())
					qBombesFinExplosion.pop();
			}
		}

}
