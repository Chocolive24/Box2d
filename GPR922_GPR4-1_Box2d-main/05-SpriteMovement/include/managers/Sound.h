
#pragma once

#include <string>
#include <iostream>

#include "SFML/Audio.hpp"

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Sound
{

private:
    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */
    Sound();

    std::vector<sf::Sound> sounds;

    // Sound FX
    sf::SoundBuffer soundFxPiou;
    sf::Sound pious;

    sf::SoundBuffer soundFxBrr;
    sf::Sound brrs;

    sf::SoundBuffer soundFxBoum;
    sf::Sound boum;

    void playOnce(sf::SoundBuffer& soundFx_);
	void playLoop(sf::SoundBuffer& soundFx_);

protected:

    static Sound* SoundManager_;

public:

    /**
     * Singletons should not be cloneable.
     */
    Sound(Sound& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Sound&) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static Sound* Instance();

    void cleanSounds();
    void cleanOneVector(std::vector<sf::Sound> sounds_);

    // --------------------
    void playPiou();
    void playBrr();
    void playBoum();


};


