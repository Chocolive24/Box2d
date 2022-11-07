#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <random>

#include "SFML/Graphics.hpp"

class Utility
{
public:

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static float PixelToMeters(float pixels);

	static sf::Vector2f MetersToPixels(b2Vec2 meters);

	// -------------------------------------------------------------------------------------
	// Template functions.

	// Generate a random number of the wanted type.
	template <typename T>
	static T GetRandomNumber(T min, T max)
	{
		std::random_device os_seed;
		uint_least32_t seed = os_seed();

		std::mt19937 generator(seed);
		std::uniform_int_distribution<uint_least32_t> distribute(min, max);

		return (T)distribute(generator);
	}
};


