#pragma once

#include "SFML/Audio.hpp"

class Sound
{
private:
	sf::Sound _laserSound;
	sf::SoundBuffer _laserBuffer;

	sf::Sound _bombSound;
	sf::SoundBuffer _bombBuffer;

	sf::Sound _bombExplosionSound;
	sf::SoundBuffer _bombExplosionBuffer;

	sf::Sound _meteorExplosionSound;
	sf::SoundBuffer _meteorExplosionBuffer;

	sf::Sound _damageSound;
	sf::SoundBuffer _damageBuffer;

public:
	Sound();

	void PlayLaserSound() { _laserSound.play(); }
	void PlayBombSound() { _bombSound.play(); }
	void StopBombSound() { _bombSound.stop(); }
	void PlayBombExplosionSound() { _bombExplosionSound.play(); }
	void PlayExplosionSound() { _meteorExplosionSound.play(); }
	void PlayDamageSound() { _damageSound.play(); }
};