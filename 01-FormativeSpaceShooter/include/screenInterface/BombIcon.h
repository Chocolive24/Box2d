#pragma once

#include "core/DrawableObject.h"
#include "SFML/Graphics.hpp"

#include "Player.h"

class BombIcon : public DrawableObject
{

public:
	BombIcon();

	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }
	sf::FloatRect GetGlobalBounds() { return _sprite.getGlobalBounds(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};