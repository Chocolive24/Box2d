#include "Utility.h"

namespace Utility
{
	b2Vec2 PixelsToMeters(sf::Vector2f pixels)
	{
		return b2Vec2(pixels.x / pixelMeterRatio, -1.0f * pixels.y / pixelMeterRatio);
	}

	float PixelToMeters(float pixels)
	{
		return pixels / pixelMeterRatio;
	}

	sf::Vector2f MetersToPixels(b2Vec2 meters)
	{
		return sf::Vector2f(meters.x * pixelMeterRatio, -1.0f * meters.y * pixelMeterRatio);
	}
}


