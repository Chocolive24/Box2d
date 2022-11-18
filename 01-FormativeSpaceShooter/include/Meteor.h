#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <core/GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MeteorExplosion.h"

class Game;

class Meteor : public GameObject
{
private:

	Game& _game;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

	b2Vec2 _velocity;
	MeteorExplosion _explosion;

	bool _isDestroyed = false;
	bool _isAnExplosion = false;
	bool _hasExploded = false;

public:
	Meteor(Game& game);
	~Meteor();

	b2Vec2 InitRndPosAndVelocity();

	void Move();

	void update(sf::Time elapsed) override;
	bool CheckIfOutOfScreen();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	b2Body* GetBody() { return _body; }
	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }
	bool HasExploded() { return _hasExploded; }
	void SetToHasExploded() { _hasExploded = true; }
};
