#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include <core/GameObject.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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
	Laser(Game& game, b2Vec2 playerPos, float angle);
	~Laser();

	// -------------------------------------------------------------------------------------------
	// Moving methods.

	void Move();

	// -------------------------------------------------------------------------------------------
	// Graphical methods.

	void CheckIfOutOfScreen();
	void update(sf::Time& elapsed) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// -------------------------------------------------------------------------------------------
	// Getters and Setters.

	b2Vec2 GetVelocity() { return _velocity; }
	void SetAngle(float omega) { _body->SetAngularVelocity(omega); }
	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }
	sf::Vector2f GetPosition() { return _sprite.getPosition(); }
	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }

	// -------------------------------------------------------------------------------------------
};
