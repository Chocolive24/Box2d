#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

using namespace std;
using namespace sf;

class Game;

class mySensor
{
public:
	explicit mySensor(Game& game_, RenderWindow& window_, Vector2f pos_, int radius_);

	void init(Vector2f pos_, int radius_);
	void update();
	void render();

	b2Body* getBody(){ return body; };
	void setColor(sf::Color color_);

private:
	// Root game
	Game& game;
	// Graphic object
	sf::CircleShape shape;
	// The SFMl Window
	sf::RenderWindow& window;
	// The box 2D object
	b2Body* body = nullptr;

};
