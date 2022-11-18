#include "weapon/BombExplosion.h"

#include <iostream>
#include <box2d/b2_circle_shape.h>

#include "Game.h"
#include "core/Utility.h"

BombExplosion::BombExplosion(Game& game) : _game(game)
{
}

void BombExplosion::Init(b2Vec2 startPosition)
{
	createSprite("data/sprites/PNG/Effects/star3.png");

	createBody(_game.GetWorld(), startPosition, b2_kinematicBody);

	sf::Vector2f position(Utility::MetersToPixels(startPosition));

	_areaOfEffect.setPosition(position.x, position.y);
	_areaOfEffect.setRadius(10.0f);
	_areaOfEffect.setOrigin(_areaOfEffect.getLocalBounds().width / 2.0f,
		_areaOfEffect.getLocalBounds().height / 2.0f);
	_areaOfEffect.setFillColor(sf::Color(150, 0, 0, 100));

	b2CircleShape hitBox;
	hitBox.m_radius = Utility::PixelToMeters(_areaOfEffect.getRadius());

	_userData = new UserData(*this);
	_userData->SetType(UserDataType::EXPLOSION);

	createFixture(hitBox, 20.0f, 0.5f,
		(uint16)UserDataType::EXPLOSION,
		(uint16)UserDataType::METEOR,
		_userData, true);
}

void BombExplosion::update(sf::Time& elapsed)
{
	GameObject::update(elapsed);

	_sprite.scale(1.01f, 1.01f);
	
	_areaOfEffect.setRadius(_areaOfEffect.getRadius() + 8);
	_areaOfEffect.setOrigin(_areaOfEffect.getGlobalBounds().width / 2.0f,
		_areaOfEffect.getGlobalBounds().height / 2.0f);

	b2CircleShape hitBox;
	hitBox.m_radius = Utility::PixelToMeters(_areaOfEffect.getRadius());

	createFixture(hitBox, 20.0f, 0.5f,
		(uint16)UserDataType::EXPLOSION,
		(uint16)UserDataType::METEOR,
		_userData, true);

	if (!_isExplosionFinished)
	{
		_duration += elapsed;

		if (_duration.asSeconds() >= 1.25f)
		{
			_isExplosionFinished = true;
			_game.GetWorld().DestroyBody(_body);
		}
	}
}

void BombExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!_isExplosionFinished)
	{
		GameObject::draw(target, states);
		target.draw(_areaOfEffect);
	}
}
