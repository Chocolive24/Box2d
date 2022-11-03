#pragma once

#include "SFML/Graphics.hpp"

#include "core/userData.h"
#include "core/box2DEntity.h"
#include "managers/soundManager.h"

class Game;

constexpr float maxAngularVelocity = 0.5;
constexpr float epsilonAngularVelocity = 0.0001;
constexpr float maxLinearVelocity = 5.0;
constexpr float epsilonLinearVelocity = 0.0001;

class Ship : public Box2DEntity
{

private:
	sf::Sprite m_sprite;

	float m_life = 100.0f;

protected:
	void createFixture(const float sizeX, const float sizeY) override;

public:

	explicit Ship(b2World& world_);

	void init(sf::Vector2u winsize);
	void update();

	void move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

	void speedUp(float force);
	void speedDown(float force);
	void ApplyLocalForceWithCheck(float force);

	void rotateLeft(float torque);
	void rotateRight(float torque);
	void ApplyTorqueWithCheck(float torque);
	void setAngularDamping(float x);;

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// getters
	float getLife();
	void setDamages(float damages_);
	constexpr float lifeMax() { return 100.0f; };

};