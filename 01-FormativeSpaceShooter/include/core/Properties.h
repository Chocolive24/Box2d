#pragma once
#include <SFML/Graphics.hpp>

class Properties
{
public:
	static constexpr float PIXEL_METER_RATIO = 100.0f;

	static constexpr float WINDOW_WIDTH = 1920.f;
	static constexpr float WINDOW_HEIGHT = 1080.f;

	inline static sf::Vector2f LEFT_DOWN_CORNER = sf::Vector2f(0, WINDOW_HEIGHT);
	inline static sf::Vector2f LEFT_UP_CORNER = sf::Vector2f(0, 0);
	inline static sf::Vector2f RIGHT_DOWN_CORNER = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
	inline static sf::Vector2f RIGHT_UP_CORNER = sf::Vector2f(WINDOW_WIDTH, 0);

	inline static sf::Color GREEN = sf::Color(0, 150, 0);
	inline static sf::Color DARK_GREEN = sf::Color(0, 50, 0);
	inline static sf::Color RED = sf::Color(150, 0, 0);

	inline static int INVINCIBILITY_EFFECT = 100;
	static constexpr float maxAngularVelocity = 0.5;
	static constexpr float epsilonAngularVelocity = 0.01f;
	static constexpr float maxLinearVelocity = 10.0;
	static constexpr float epsilonLinearVelocity = 0.01f;

	static constexpr int METEOR_POINTS = 10;
	static constexpr int METEOR_DAMAGE = 20;

	static constexpr float TITLE_WAVE_TIME = 2.0f;
	static constexpr float LASER_COOLDOWN = 0.2f;
	static constexpr float BOMB_COOLDOWN = 2.0f;
	static constexpr float METEOR_COOLDOWN = 1.0f;

	static constexpr float COLLI_WITH_METEOR_CD = 1.0f;

	static constexpr float INVINCIBILITY_TIME = 3.0f;
};