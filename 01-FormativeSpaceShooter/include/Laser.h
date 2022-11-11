#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <core/GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;

class Laser : public GameObject
{
private:
	Game& _game;

	// Shape of the physical (A box)
	b2PolygonShape _hitBox;

	b2Vec2 _velocity;

	bool _isDestroyed = false;

	

public:
	Laser(Game& game, b2Vec2 playerPos);
	~Laser();

	b2Vec2 GetVelocity() { return _velocity; }
	void SetAngle(float omega) { _body->SetAngularVelocity(omega); }
	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }
	void CheckIfOutOfScreen();


	void Init(b2World& world, b2Vec2 playerPos);

	void Move(b2Vec2 force);

	sf::Vector2f GetPosition() { return _sprite.getPosition(); }

	void update(sf::Time elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
