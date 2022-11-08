#pragma once
#include <SFML/Graphics.hpp>

class Properties
{
public:
	static constexpr float PIXEL_METER_RATIO = 100.0f;

	static constexpr float WINDOW_WIDTH = 1200.0f;
	static constexpr float WINDOW_HEIGHT = 900.0f;

	/*static sf::Clock CLOCK;
	static sf::Time TOTALELAPSED;
	static sf::Time ELAPSED;

	static constexpr float BOMBMOVEMENT = 1000.0f / 500.0f;*/

	static void UpdateTime();
};
