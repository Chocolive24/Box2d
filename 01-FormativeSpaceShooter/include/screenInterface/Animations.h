#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Animations
{
private:
	Player& _player;

	sf::Time _totalDuration;
	sf::Time _alphaEffectDuration;

	bool _playAnimation = false;

public:
	Animations(Player& player);

	void PlayDamageAnimation(sf::Time elapsed);

	void Update(sf::Time elapsed);

	void CanPlayAnimation(bool canPlay) { _playAnimation = canPlay; }
};
