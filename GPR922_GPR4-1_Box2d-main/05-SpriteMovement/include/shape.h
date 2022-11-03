
#pragma once

#include "SFML/Graphics.hpp"
#include <random>

class Shape : public sf::Drawable
{

private:
	sf::RectangleShape m_shape;
	bool isTouched = false;

public:
	Shape(sf::RenderWindow& window_);

	void update();
	void checkTouch(sf::Vector2f mousePosition);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool getIsTouched() { return isTouched; };

};