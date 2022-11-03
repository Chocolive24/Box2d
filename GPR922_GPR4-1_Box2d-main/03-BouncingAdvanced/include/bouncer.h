#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer
{
public:
	explicit Bouncer(Game& game_, sf::RenderWindow& window_, sf::Vector2f, sf::Vector2f);

	void init(sf::Vector2f, sf::Vector2f);
	void update();
	void render();

	b2Body* getBody(){ return body; };

private:
	// Root game
	Game& game;
	// Graphic object
	sf::RectangleShape shape;
	sf::ConvexShape boxShape;
	// The SFMl Window
	sf::RenderWindow& window;
	// The box 2D object
	b2Body* body = nullptr;

};
