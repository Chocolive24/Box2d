#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>

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
	// Body and fixture attributes.
	b2Body* _body = nullptr;

	b2FixtureDef _fixtureDef;

	// ---------------------------------------------------------------------------------------------------
	// Methods to create the sprite, the body and the fixture.
	void createSprite(std::string path);

	void createBody(b2World& world, b2Vec2 startPosition);

	b2PolygonShape createPolygonHitBox();
	b2CircleShape createCicrleHitBox();

	void createFixture(b2Shape& hitBox, void* thisPtr);

	// ---------------------------------------------------------------------------------------------------
	// Methods related to the game loop.

	virtual void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// ---------------------------------------------------------------------------------------------------
};