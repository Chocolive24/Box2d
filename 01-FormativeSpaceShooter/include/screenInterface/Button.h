#pragma once

#include "GameText.h"
#include "core/DrawableObject.h"
#include "SFML/Graphics.hpp"

class Button : public DrawableObject
{
private:
	sf::RectangleShape _shape;

	GameText _buttonText;

	sf::Texture _texture;
	sf::Sprite _sprite;
	std::map<std::string, sf::Sprite> _keySprites;

public:
	void SetText(std::string newText) { _buttonText.SetString(newText); }
	sf::Vector2f GetPosition() { return _shape.getPosition(); }
	void SetPosition(float x, float y);
	void SetTextOriginToMiddle() { _buttonText.SetOriginToMiddle(); }

	void Init(float x, float y, sf::Vector2f size, std::string string, int charSize, std::string path);
	void InitShape(float x, float y, sf::Vector2f size);
	void InitText(std::string string, int charSize);
	void InitKeySprite(std::string path);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};