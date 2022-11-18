#pragma once
#include "core/GameObject.h"

class Game;

class BombExplosion : public GameObject
{
private:
	Game& _game;

	sf::CircleShape _areaOfEffect;

	bool _isExplosionFinished = false;

	sf::Time _duration;

public:
	BombExplosion(Game& game);

	bool IsExplosionFinished() { return _isExplosionFinished; }
	void SetExplosionToFinished() { _isExplosionFinished = true; }

	void Init(b2Vec2 startPosition);

	void update(sf::Time& elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};