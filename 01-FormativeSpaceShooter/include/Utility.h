#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include "SFML/Graphics.hpp"

namespace Utility
{
	constexpr float pixelMeterRatio = 100.0f;

	b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	float PixelToMeters(float pixels);

	sf::Vector2f MetersToPixels(b2Vec2 meters);
};