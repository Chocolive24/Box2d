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

	b2Vec2 _velocity;

	bool _isDestroyed = false;
	bool _canExplose = true;

public:
	Meteor(Game& game);
	~Meteor();

	b2Vec2 InitRndPosAndVelocity();

	void Move();

	void update(sf::Time& elapsed) override;
	bool CheckIfOutOfScreen();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	b2Body* GetBody() { return _body; }
	bool IsDestroyed() { return _isDestroyed; }
	void SetToDestroyed() { _isDestroyed = true; }
	bool CanExplose() { return _canExplose; }
};
