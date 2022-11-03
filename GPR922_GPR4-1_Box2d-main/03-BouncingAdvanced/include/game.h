#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "ball.h"
#include "bouncer.h"

using namespace std;
using namespace sf;

class Game{
public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return world_; };

	static b2Vec2 pixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 pixelsToMeters(sf::Vector2u pixels);
	static float pixelsToMeters(float pixels);
	static sf::Vector2f metersToPixels(b2Vec2 meters);

	static const float pixelsMetersRatio;

private:

	// The window ---------------------------------------------
	RenderWindow window_;

	// The physical world -------------------------------------
	b2Vec2 gravity_;
	b2World world_;

	Ball theBall;
	vector<Bouncer> bouncers;

#pragma region Physical world methods
	void clearBouncers();
#pragma endregion


	Vector2f mousePressedPos_bouncer, mouseReleasedPos_bouncer;
	Vector2f mousePressedPos_ball, mouseReleasedPos_ball;

};
