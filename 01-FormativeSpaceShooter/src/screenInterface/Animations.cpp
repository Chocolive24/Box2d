#include "screenInterface/Animations.h"

#include "core/Properties.h"

Animations::Animations(Player& player) : _player(player)
{
}

void Animations::CollisionWithMeteorAnim(sf::Time& elapsed, bool& isACollision)
{
	if (isACollision)
	{
		//_player.GetBody()->ApplyTorque(balbal)

		_duration += elapsed;

		Properties::INVINCIBILITY_EFFECT *= -1;

		_player.GetSprite().setColor(sf::Color(_player.GetSprite().getColor().r,
			_player.GetSprite().getColor().g,
			_player.GetSprite().getColor().b,
			_player.GetSprite().getColor().a - Properties::INVINCIBILITY_EFFECT));

		if (_duration.asSeconds() < Properties::COLLI_WITH_METEOR_CD)
		{
			_player.GetSprite().rotate(-10.0f);
		}

		else
		{
			_player.GetSprite().setRotation(0.0f);
		}

		if (_duration.asSeconds() >= Properties::INVINCIBILITY_TIME)
		{
			_player.GetSprite().setColor(sf::Color(_player.GetSprite().getColor().r,
				_player.GetSprite().getColor().g,
				_player.GetSprite().getColor().b,
				255));
			Properties::INVINCIBILITY_EFFECT = +(Properties::INVINCIBILITY_EFFECT);
			isACollision = false;
		}
	}
}
