#pragma once
#include "core/GameObject.h"


class Game;

class Explosion : public GameObject
{
private:

	Game& _game;

	sf::CircleShape _areaOfEffect;

	bool _isExplosionFinished = false;

	sf::Time _duration;

public:
	Explosion(Game& game);
	~Explosion();

	bool IsExplosionFinished() { return _isExplosionFinished; }
	void SetExplosionToFinished() { _isExplosionFinished = true; }

	void Init(Game& game, b2Vec2 meteorPosition);

	void update(sf::Time elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
