#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "SFML_Utilities.h"

#include "ball.h"
#include "bouncer.h"
#include "contact_listener.h"
#include "mySensor.h"
#include "user_data.h"


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
	MyContactListener contactListener_;

	Ball theBall;
	vector<Bouncer> windowLimits;
	vector<mySensor> sensors;

#pragma region Physical world methods
	void clearBouncers();
	//void BeginContact(UserDataType userData, UserDataType userData1);
	//void EndContact(UserDataType userData, UserDataType userData1);
#pragma endregion

	Vector2f mousePressedPos_sensor, mouseReleasedPos_sensor;
	Vector2f mousePressedPos_ball, mouseReleasedPos_ball;

};
