#pragma once

#include "SFML/Audio.hpp"

class SoundManager
{
private:
	sf::Sound _laserSound;
	sf::SoundBuffer _laserBuffer;

	sf::Sound _bombSound;
	sf::SoundBuffer _bombBuffer;

	sf::Sound _explosionSound;
	sf::SoundBuffer _explosionBuffer;

public:
	SoundManager();

	void PlayLaserSound() { _laserSound.play(); }
	void PlayBombSound() { _bombSound.play(); }
	void PlayExplosionSound() { _explosionSound.play(); }
};