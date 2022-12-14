#pragma once

#include "SFML/Graphics.hpp"

class GameText : public sf::Drawable
{
protected:
	sf::Font _font;
	sf::Text _text;

public:
	void Init(std::string string, float x, float y, int charSize, sf::Color color);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetTextPosition(float x, float y) { _text.setPosition(x, y); }
	void SetOriginToMiddle() { _text.setOrigin(_text.getLocalBounds().width / 2.0f,
												_text.getLocalBounds().height / 2.0f);}

	void SetString(std::string newText) { _text.setString(newText); }
	sf::FloatRect GetLocalBounds() { return _text.getLocalBounds(); }
};