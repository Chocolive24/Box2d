#pragma once

#include <box2d/b2_world.h>

#include "SFML/Graphics.hpp"

class Utility
{
public:

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static float PixelToMeters(float pixels);

	static float DegToRad(float degrees);
	static float RadToDeg(float radians);

	static sf::Vector2f MetersToPixels(b2Vec2 meters);

	static float GetRandomFloat(float min, float max);
	static int GetRandomInt(int min, int max);

};