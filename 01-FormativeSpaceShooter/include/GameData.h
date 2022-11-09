#pragma once

#include "SFML/Graphics.hpp"

class GameData : public sf::Drawable
{
private:

	sf::Texture _texture;
	sf::Sprite _sprite;

public:
	void CreateSprite();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};