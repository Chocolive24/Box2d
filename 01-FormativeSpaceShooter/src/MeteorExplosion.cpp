#include "MeteorExplosion.h"

MeteorExplosion::MeteorExplosion(sf::Vector2f startPosition)
{
	InitSprite("data/sprites/PNG/Effects/regularExplosion01.png");
	_sprite.setPosition(startPosition);
}

void MeteorExplosion::Update(sf::Time& elapsed)
{
	_sprite.scale(1.01f, 1.01f);

	if (!_isExplosionFinished)
	{
		_duration += elapsed;

		if (_duration.asSeconds() >= 1)
		{
			_isExplosionFinished = true;
		}
	}
}

void MeteorExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!_isExplosionFinished)
	{
		DrawableObject::draw(target, states);
	}
}