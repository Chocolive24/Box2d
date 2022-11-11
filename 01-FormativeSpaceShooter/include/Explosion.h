#pragma once
#include "core/GameObject.h"


class Game;

class Explosion : public GameObject
{
private:

	Game& _game;

	sf::CircleShape _areaOfEffect;

	bool _isAnExplosion = false;
	bool _isExplosionFinished = false;
	bool _isDestroyed = false;

	sf::Time _duration;

public:
	Explosion(Game& game);
	~Explosion();
	bool IsAnExplosion() { return _isAnExplosion; }
	void CreateAnExplosion() { _isAnExplosion = true; }
	void SetExplosionToFinished() { _isExplosionFinished = true; }

	void SetToDestroyed() { _isDestroyed = true; }

	void Init(Game& game, b2Vec2 meteorPosition);

	void update(sf::Time elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
