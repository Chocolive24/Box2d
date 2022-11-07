#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Laser : public sf::Drawable
{
private:
	// ------------------------------------------------
	// Sprite

	sf::Texture _texture;
	sf::Sprite _sprite;

	// ------------------------------------------------
	// Box 2d

	b2BodyDef _bodyDef;

	b2Body* _body = nullptr;

	// Shape of the physical (A box)
	b2PolygonShape _hitBox;

	// The fixture is what it defines the physic react
	b2FixtureDef FixtureDef;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

public:
	void Init(b2World& world, b2Vec2 playerPos);

	void Move(b2Vec2 force);

	void PlaySound() { _sound.play(); }

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
