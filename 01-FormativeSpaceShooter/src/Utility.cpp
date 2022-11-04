#include "Utility.h"

#include "Properties.h"

b2Vec2 Utility::PixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / Properties::PIXEL_METER_RATIO, -1.0f * pixels.y / Properties::PIXEL_METER_RATIO);
}

float Utility::PixelToMeters(float pixels)
{
	return pixels / Properties::PIXEL_METER_RATIO;
}

sf::Vector2f Utility::MetersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * Properties::PIXEL_METER_RATIO, -1.0f * meters.y * Properties::PIXEL_METER_RATIO);
}
