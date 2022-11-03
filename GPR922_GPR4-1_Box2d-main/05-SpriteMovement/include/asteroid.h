#pragma once

#include <random>

#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "core/SFML_Utilities.h"
#include "core/box2DEntity.h"
#include "core/userData.h"

#include "managers/textureManager.h"

class Asteroid : public Box2DEntity
{
public:
	Asteroid(b2World& world_, sf::Vector2f size_);
	//~Asteroid();

	void setIsDead();
	bool getIsDead();

	long getLocalId();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite	m_sprite;
	bool m_isDead = false;

	static long m_localIdAsteroid;
	static long getGlobalId();

protected:
	void createFixture(const float sizeX, const float sizeY) override;

};
