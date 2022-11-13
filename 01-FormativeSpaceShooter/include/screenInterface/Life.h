#pragma once

#include "Player.h"
#include "SFML/Graphics.hpp"

class Player;

class Life : public sf::Drawable, public sf::Transformable
{
private:
	Player& _player;

	sf::Texture _texture;
	sf::Sprite _sprite;

	bool _isLost = false;

public:
	Life(Player& player);

	bool IsLost() { return _isLost; }
	void SetToLost() { _isLost = true; }
	sf::FloatRect GetLocalBounds() { return _sprite.getLocalBounds(); }

	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
