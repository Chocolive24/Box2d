#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer
{
public:
	explicit Bouncer(Game& game_, sf::RenderWindow& window_);

	void init();
	void update();
	void render();

private:
	// Root game
	Game& game;
	// Graphic object
	sf::RectangleShape shape;
	// The SFMl Window
	sf::RenderWindow& window;
	// The box 2D object
	b2Body* body = nullptr;

};
