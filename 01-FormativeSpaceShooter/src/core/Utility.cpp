#include "core/Utility.h"

#include <corecrt_math_defines.h>
#include <random>

#include "core/Properties.h"

b2Vec2 Utility::PixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / Properties::PIXEL_METER_RATIO, -1.0f * pixels.y / Properties::PIXEL_METER_RATIO);
}

float Utility::PixelToMeters(float pixels)
{
	return pixels / Properties::PIXEL_METER_RATIO;
}

float Utility::DegToRad(float degrees)
{
	return (degrees * M_PI / 180.0f);
}

float Utility::RadToDeg(float radians)
{
	
	return (radians / M_PI * 180.0f);
}

sf::Vector2f Utility::MetersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * Properties::PIXEL_METER_RATIO, -1.0f * meters.y * Properties::PIXEL_METER_RATIO);
}

float Utility::GetRandomFloat(float min, float max)
{
	std::random_device os_seed;
	uint_least32_t seed = os_seed();

	std::mt19937 generator(seed);
	std::uniform_real<float> distribute(min, max);

	return (float)distribute(generator);
}

int Utility::GetRandomInt(int min, int max)
{
	std::random_device os_seed;
	uint_least32_t seed = os_seed();

	std::mt19937 generator(seed);
	std::uniform_int_distribution<uint_least32_t> distribute(min, max);

	return (int)distribute(generator);
}