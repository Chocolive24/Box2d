#pragma once

#include "Player.h"
#include "SFML/Graphics.hpp"

class Player;

class Life : public DrawableObject
{
private:
	Player& _player;

	bool _isLost = false;

	sf::Time _duration;

public:
	Life(Player& player);

	void Update(sf::Time& elapsed, std::list<Life>& lives);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool IsLost() { return _isLost; }
	void SetToLost() { _isLost = true; }

	sf::FloatRect GetLocalBounds() { return _sprite.getLocalBounds(); }

	sf::Vector2f GetPosition() { return _sprite.getPosition(); }
	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }
};
