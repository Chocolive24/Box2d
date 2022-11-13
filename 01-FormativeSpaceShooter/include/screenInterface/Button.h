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
	void SetText(std::string newText) { _text.setString(newText); }
	void SetPosition(float x, float y);

	void Init(float x, float y, sf::Vector2f size, std::string string, std::string path);
	void InitShape(float x, float y, sf::Vector2f size);
	void InitText(std::string string);
	void InitKeySprite(std::string path);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};