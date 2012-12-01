
#include "Son.h"

using namespace std;

/**
 * Constructeur par default (charge tout les fichiers sons necessaires)
 */
Son::Son(){
	// On charge le .ogg pour le thème du menu
	if (!menu.OpenFromFile("audio/menu.ogg")){
		cout << "Erreur lors du chargement du thème de menu " << endl;
	}
	// On charge le .wav pour les explosions dans un buffer
	if (!bufferExplosion.LoadFromFile("audio/explosion.wav")) {
		cout<< " Erreur lors du chargement du bruitage explosion" << endl;
	}
	// On utilise ce buffer dans un objet de type Sound
	explosion.SetBuffer(bufferExplosion);

    // On charge le .wav pour les bonus
	if (!bufferBonus.LoadFromFile("audio/bonus.wav")) {
		cout<< " Erreur lors du chargement du bruitage bonus" << endl;
	}
	// On utilise ce buffer dans un objet de type Sound
	bonus.SetBuffer(bufferBonus);
}


/**
 * Chargement des sons spécifiques en fonction du theme de la carte
 *
 * @Param std::string themeCarte : Theme de la carte
 *
 * @Return void
 */
void Son::chargerSons(std::string themeCarte){

	// Chemin du son en fonction du nom du theme
	std::string pathTheme = "audio/" + themeCarte + ".ogg";
	// Chemin du son de victoire en fonction du nom du theme
	std::string pathWin = "audio/" + themeCarte + "Win.ogg";

	// On charge le .ogg pour le thème musical
	if (!sound.OpenFromFile(pathTheme.c_str())){
		cout << "Erreur lors du chargement du thème musical " << endl;
	}
	// On charge le .ogg pour le thème de la victoire
	if (!win.OpenFromFile(pathWin.c_str())){
		cout << "Erreur lors du chargement du thème de victoire " << endl;
	}
}

/**
 * Joue le thème musicale
 *
 * @Return void
 */
void Son::playMusic() {
	// On stop dabord la musique de la victoire
	win.Stop();
	// Puis on joue la musique du jeu
	sound.Play();
	sound.SetLoop(true);
}

/**
 * Joue le thème de la victoire
 *
 * @Return void
 */
void Son::playWin() {
	// On stop dabord la musique du jeu
	sound.Stop();
	// Puis on joue le thème de la victoire
	win.Play();
}

/**
 * Joue les explosions
 *
 * @Return void
 */

void Son::playExplosion() {
	explosion.Play();
}

/**
 * Joue le son des bonus
 *
 * @Return void
 */
void Son::playBonus() {
	bonus.Play();
}

/**
 * Stop le thème de victoire et la musique du jeu
 *
 * @Return void
 */
 void Son::stopMusic(){
     win.Stop();
     sound.Stop();
 }



