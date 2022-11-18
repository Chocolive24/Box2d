#include "screenInterface/Animations.h"

#include <iostream>

#include "core/Properties.h"

Animations::Animations(Player& player) : _player(player)
{
}

void Animations::PlayDamageAnimation(sf::Time elapsed)
{
	_totalDuration += elapsed;
	_alphaEffectDuration += elapsed;

	if (_alphaEffectDuration.asSeconds() >= 0.1)
	{
		Properties::INVINCIBILITY_EFFECT = -1 * Properties::INVINCIBILITY_EFFECT;

		_player.GetSprite().setColor(sf::Color(_player.GetSprite().getColor().r,
			_player.GetSprite().getColor().g,
			_player.GetSprite().getColor().b,
			_player.GetSprite().getColor().a - Properties::INVINCIBILITY_EFFECT));

		_alphaEffectDuration = sf::Time::Zero;
	}

	if (_totalDuration.asSeconds() <= Properties::COLLI_WITH_METEOR_CD)
	{
		_player.SetControl(false);
		_player.GetBody()->SetAngularVelocity(15.0f);
	}

	else
	{
		_player.SetControl(true);
	}

	if (_totalDuration.asSeconds() >= Properties::INVINCIBILITY_TIME - 0.1f)
	{
		_player.GetSprite().setColor(sf::Color(255, 255, 255, 255));
		Properties::INVINCIBILITY_EFFECT = +Properties::INVINCIBILITY_EFFECT;
	}

	if (_totalDuration.asSeconds() >= Properties::INVINCIBILITY_TIME)
	{
		_totalDuration = sf::Time::Zero;
	}
}

void Animations::Update(sf::Time elapsed)
{
	if (_player.IsInvincible())
	{
		PlayDamageAnimation(elapsed);
	}
}