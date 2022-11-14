#pragma once

#include "SFML/Graphics.hpp"

class GameText : public sf::Drawable
{
protected:
	sf::Font _font;
	sf::Text _text;

public:

	void SetTextPosition(float x, float y) { _text.setPosition(x, y); }
	void SetOriginToMiddle() { _text.setOrigin(_text.getGlobalBounds().width / 2.0f,
																_text.getGlobalBounds().height / 2.0f); }
	sf::FloatRect GetGlobalBounds() { return _text.getGlobalBounds(); }

	void Init(std::string string, float x, float y, int charSize, sf::Color color);

	void SetString(std::string newText) { _text.setString(newText); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};