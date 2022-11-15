#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Animations
{
private:
	Player& _player;

	sf::Time _duration;

public:
	Animations(Player& player);

	void CollisionWithMeteorAnim(sf::Time& elapsed, bool& isACollision);
};
