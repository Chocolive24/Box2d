#pragma once

#include "SFML/Graphics.hpp"

class Player;

class LifeBar : public  sf::Drawable
{
private:
	Player& _player;

	sf::RectangleShape _currentLifeBar;
	sf::RectangleShape _damagedLifeBar;

public:
	LifeBar(Player& player);

	sf::Vector2f GetPosition() { return _damagedLifeBar.getPosition(); }
	sf::FloatRect GetLocalBounds() { return _damagedLifeBar.getLocalBounds(); }

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
