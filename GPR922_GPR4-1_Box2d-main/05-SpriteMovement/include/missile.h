#pragma once
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_fixture.h>

#include "core/box2DEntity.h"

class Missile : public Box2DEntity
{
public:
	Missile(b2World& world_, const sf::Vector2f startPos_, const float angle_);
	//~Missile();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void setIsDead();
	bool getIsDead();

	long getLocalId();

private:
	sf::Sprite	m_sprite;
	bool m_isDead = false;

	static long m_localIdMissile;
	static long getGlobalId();

protected:
	void createFixture(const float sizeX, const float sizeY) override;

};
