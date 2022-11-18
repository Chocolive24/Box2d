#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "DrawableObject.h"
#include <SFML/Graphics.hpp>
#include "UserData.h"

// Class that creates the game's main objects.
// All game objects has physical attributes and a sprite.
class GameObject : public DrawableObject
{
protected:
	// ---------------------------------------------------------------------------------------------------
	// Body, User data and fixture attributes.
	b2Body* _body = nullptr;

	UserData* _userData = nullptr;
	bool _addedToGroupIndex = false;

	b2Shape* _shape;

	b2Fixture* _fixture;

	b2FixtureDef _fixtureDef;

	// ---------------------------------------------------------------------------------------------------
	// Methods to create the sprite, the body and the fixture.
	void createSprite(std::string path);

	void createBody(b2World& world, b2Vec2 startPosition, b2BodyType type);

	b2PolygonShape createPolygonHitBox();
	b2CircleShape createCicrleHitBox();

	void createFixture(b2Shape& hitBox, float density, float restitution,
						uint16 categoryBits, uint16 maskBits, UserData* userData, bool isSensor);

	// ---------------------------------------------------------------------------------------------------
	// Methods related to the game loop.

	virtual void update(sf::Time elapsed);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// ---------------------------------------------------------------------------------------------------

public:
	void setIsSensor(bool isSensor) { _fixtureDef.isSensor = isSensor; }
};