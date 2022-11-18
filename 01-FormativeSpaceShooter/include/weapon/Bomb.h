#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <core/GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "BombExplosion.h"

class Game;

class Bomb : public GameObject
{
private:
	Game& _game;

	b2Vec2 _velocity;

	BombExplosion _explosion;

	bool _isDestroyed = false;
	bool _isAnExplosion = false;
	bool _hasExploded = false;
	bool _mustPlayExplosionSound = true;

	sf::Time _duration;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

public:
	Bomb(Game& game, b2Vec2 playerPos, float angle);
	~Bomb();


	b2Body* GetBody() { return _body; }
	bool IsDestroyed() { return _isDestroyed; }
	bool HasExploded() { return _hasExploded; }
	void SetToHasExploded() { _hasExploded = true; }
	void SetToDestroyed() { _isDestroyed = true; }

	void Init(b2World& world, b2Vec2 playerPos);

	void Move();

	void PlaySound() { _sound.play(); }

	void update(sf::Time elpased) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};