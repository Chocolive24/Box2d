#pragma once

#include "SFML/Graphics.hpp"

class Button : public sf::Drawable
{
private:
	sf::RectangleShape _shape;
	sf::Font _font;

	sf::Text _text;

	sf::Texture _texture;
	sf::Sprite _sprite;
	std::map<std::string, sf::Sprite> _keySprites;

public:
	void Init(float x, float y, std::string string, std::string path);
	void InitShape(float x, float y);
	void InitText(std::string string);
	void InitKeySprite(std::string path);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};