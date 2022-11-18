#include "weapon/Bomb.h"

#include <iostream>
#include <Box2D/b2_circle_shape.h>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Bomb::Bomb(Game& game, b2Vec2 playerPos, float angle) : _game(game), _explosion(_game)
{
    createSprite("data/sprites/PNG/Lasers/laserRed08.png");

    createBody(_game.GetWorld(), playerPos, b2_dynamicBody);

    _body->SetTransform(playerPos, Utility::DegToRad(angle));

    _velocity = b2Vec2(0.0f, 1.5f);

    b2Vec2 initialVelocity = _body->GetLocalVector(_velocity);
    _body->SetLinearVelocity(initialVelocity);

    b2CircleShape hitBox = createCicrleHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::BOMB);

    createFixture(hitBox, 2.0f, 0.5f, 
				  (int16)_userData->GetType(),
		          (uint16)UserDataType::LASER | (uint16)UserDataType::METEOR,
		          _userData, false);
}

Bomb::~Bomb()
{
    _game.GetWorld().DestroyBody(_body);
}

void Bomb::update(sf::Time& elapsed)
{
    GameObject::update(elapsed);

    _duration += elapsed;

    if (_duration.asSeconds() >= Properties::BOMB_COOLDOWN)
    {
        _isDestroyed = true;

        if (_mustPlayExplosionSound)
        {
            _game.GetSoundManager().PlayBombExplosionSound();
            _mustPlayExplosionSound = false;
        }
        
    }

    if (_isDestroyed && !_isAnExplosion)
    {
        _explosion.Init(_body->GetPosition());
        _isAnExplosion = true;
    }

    if (_isAnExplosion)
    {
        _explosion.update(elapsed);

        if (_explosion.IsExplosionFinished())
        {
            _hasExploded = true;
        }
    }
}


void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!_isDestroyed)
    {
        GameObject::draw(target, states);
    }

    else
    {
        target.draw(_explosion);
    }
}