#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;

class Bomb : public GameObject
{
private:
	Game& _game;

	bool _isDestroyed = false;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

public:
	Bomb(Game& game, b2Vec2 playerPos);
	~Bomb();

	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }

	void Init(b2World& world, b2Vec2 playerPos);

	void Move(b2Vec2 force);

	void PlaySound() { _sound.play(); }

	void update(sf::Time elpased) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};