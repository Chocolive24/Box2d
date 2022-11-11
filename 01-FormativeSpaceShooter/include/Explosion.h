#pragma once
#include "core/GameObject.h"


class Game;

class Explosion : public GameObject
{
private:

	Game& _game;

public:
	Explosion(Game& game, b2Vec2 meteorPosition);

	void update(sf::Time elapsed) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
