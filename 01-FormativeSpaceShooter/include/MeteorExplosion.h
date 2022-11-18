#pragma once

#include "core/DrawableObject.h"
#include "SFML/Graphics.hpp"

class MeteorExplosion : public DrawableObject
{
private:
	sf::Time _duration;

	bool _isExplosionFinished = false;

public:
	MeteorExplosion(sf::Vector2f startPosition);

	void Update(sf::Time& elapsed);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool IsExplosionFinished() { return _isExplosionFinished; }
	void SetExplosionToFinished() { _isExplosionFinished = true; }
};