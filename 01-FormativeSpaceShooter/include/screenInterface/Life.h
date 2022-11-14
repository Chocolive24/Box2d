#pragma once

#include "Player.h"
#include "SFML/Graphics.hpp"

class Player;

class Life : public DrawableObject
{
private:
	Player& _player;
	Game& _game;

	bool _isLost = false;

	sf::Time _duration;

public:
	Life(Player& player, Game& game);

	bool IsLost() { return _isLost; }
	void SetToLost() { _isLost = true; }
	sf::FloatRect GetLocalBounds() { return _sprite.getLocalBounds(); }

	sf::Vector2f GetPosition() { return _sprite.getPosition(); }
	void SetPosition(float x, float y) { _sprite.setPosition(x, y); }

	void Update(sf::Time elapsed, std::list<Life>& lives);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
