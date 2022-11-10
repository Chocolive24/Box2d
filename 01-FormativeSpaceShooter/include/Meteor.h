#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;

class Meteor : public GameObject
{
private:

	Game& _game;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

	b2Vec2 _velocity;

	bool _isDestroyed = false;

public:
	Meteor(Game& game);
	~Meteor();

	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }

	void Init(b2World& world);

	b2Vec2 InitRndPosAndVelocity();

	void Move();

	void SetColor() { _sprite.setColor(sf::Color::Black); }

	void update(sf::Time elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
