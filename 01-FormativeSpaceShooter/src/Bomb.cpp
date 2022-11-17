#include "Bomb.h"

#include <iostream>
#include <Box2D/b2_circle_shape.h>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Bomb::Bomb(Game& game, b2Vec2 playerPos) : _game(game), _explosion(_game)
{
    createSprite("data/sprites/PNG/Lasers/laserRed08.png");

    createBody(_game.GetWorld(), playerPos, b2_kinematicBody);
    b2CircleShape hitBox = createCicrleHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::BOMB);

    createFixture(hitBox, 2.0f, 0.5f, 
				  (int16)_userData->GetType(),
		          (uint16)UserDataType::METEOR | (uint16)UserDataType::LASER,
		          _userData, false);

    _velocity = b2Vec2(0.0f, 1.5f);
}

Bomb::~Bomb()
{
    _game.GetWorld().DestroyBody(_body);
}

void Bomb::Move()
{
    _body->SetLinearVelocity(_velocity);
}

void Bomb::update(sf::Time elapsed)
{
    GameObject::update(elapsed);

    _duration += elapsed;

    if (_duration.asSeconds() >= Properties::BOMB_COOLDOWN)
    {
        _isDestroyed = true;
    }

    if (_isDestroyed && !_isAnExplosion)
    {
        _explosion.Init(_game, _body->GetPosition());
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