#pragma once

#include "core/DrawableObject.h"
#include "SFML/Graphics.hpp"

#include "Player.h"

class BombUI : public DrawableObject
{
private:
	Player& _player;
	Game& _game;

	bool _wasUsed = false;

	sf::Time _duration;

public:
	BombUI(Player& player, Game& game);

	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }
	sf::FloatRect GetGlobalBounds() { return _sprite.getGlobalBounds(); }

	bool WasUsed() { return _wasUsed; }
	void SetToUsed() { _wasUsed = true; }

	void Update(sf::Time elapsed, std::list<BombUI>& bombsUI);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
