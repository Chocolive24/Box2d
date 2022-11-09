#pragma once
#include <SFML/Graphics.hpp>

class Properties
{
public:
	static constexpr float PIXEL_METER_RATIO = 100.0f;

	static constexpr float WINDOW_WIDTH = 1500.0f;
	static constexpr float WINDOW_HEIGHT = 900.0f;

	inline static sf::Color GREEN = sf::Color(0, 150, 0);
	inline static sf::Color DARKGREEN = sf::Color(0, 50, 0);

	/*static sf::Clock CLOCK;
	static sf::Time TOTALELAPSED;
	static sf::Time ELAPSED;

	static constexpr float BOMBMOVEMENT = 1000.0f / 500.0f;*/

	static void UpdateTime();
};
