#pragma once

#include "core/DrawableObject.h"
#include "SFML/Graphics.hpp"

class Player;

class LifeBar : public  DrawableObject 
{
private:
	Player& _player;

	sf::RectangleShape _currentLifeBar;
	sf::RectangleShape _damagedLifeBar;

public:
	LifeBar(Player& player);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f GetPosition() { return _damagedLifeBar.getPosition(); }
	sf::FloatRect GetLocalBounds() { return _damagedLifeBar.getLocalBounds(); }
};
