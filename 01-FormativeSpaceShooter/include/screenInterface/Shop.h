#pragma once

#include "SFML/Graphics.hpp"

class Shop : public sf::Drawable
{
private:

public:

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};