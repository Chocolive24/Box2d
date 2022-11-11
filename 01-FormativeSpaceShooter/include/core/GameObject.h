#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>

#include "UserData.h"

/**
 * \brief Class that create basics game objects elements.
 */
class GameObject : public sf::Drawable, public sf::Transformable
{
protected:
	// ---------------------------------------------------------------------------------------------------
	// Sprite attributes.

	sf::Texture _texture;
	sf::Sprite _sprite;

	// ---------------------------------------------------------------------------------------------------
	// Body, User data and fixture attributes.
	b2Body* _body = nullptr;

	UserData* _userData = nullptr;
	bool _addedToGroupIndex = false;

	b2FixtureDef _fixtureDef;

	sf::Time _totalElapsed;

	// ---------------------------------------------------------------------------------------------------
	// Methods to create the sprite, the body and the fixture.
	void createSprite(std::string path);

	void createBody(b2World& world, b2Vec2 startPosition);

	

	b2PolygonShape createPolygonHitBox();
	b2CircleShape createCicrleHitBox();

	void createFixture(b2Shape& hitBox, int16 userDataIndex, UserData* userData);

	// ---------------------------------------------------------------------------------------------------
	// Methods related to the game loop.

	virtual void update(sf::Time elapsed);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// ---------------------------------------------------------------------------------------------------
};