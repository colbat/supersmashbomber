#ifndef DEF_SON
#define DEF_SON
#include <SFML/Audio.hpp>
#include <iostream>

class Son
{
 public:
    /* --- Constructeur --- */
    Son();
    /* --- Méthodes ---*/
	void chargerSons(std::string themeCarte);
    void playMusic();
    void playWin();
    void playExplosion();
    void playMenu();
    void playBonus();
    void stopMusic();

 private:
    /* --- Buffers --- */
    sf::SoundBuffer bufferExplosion;
    sf::SoundBuffer bufferBonus;

    /* --- Musiques ---*/
    sf::Music sound;
    sf::Music menu;
    sf::Music win;

    /* --- Sons --- */
    sf::Sound explosion;
    sf::Sound bonus;

};
#endif
