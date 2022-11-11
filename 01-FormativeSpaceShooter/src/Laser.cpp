#include "Laser.h"

#include <iostream>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Laser::Laser(Game& game, b2Vec2 playerPos) : _game(game)
{
    createSprite("data/sprites/PNG/Lasers/laserRed01.png");

    createBody(_game.GetWorld(), playerPos);
    _hitBox = createPolygonHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::LASER);

    createFixture(_hitBox, (int)_userData->GetType(), _userData);

    _velocity = b2Vec2(0.0f, 10.0f);
}

Laser::~Laser()
{
    _game.GetWorld().DestroyBody(_body);
    std::cout << _isDestroyed << std::endl;
}

void Laser::CheckIfOutOfScreen()
{
    if (_body->GetPosition().y >= 0 || 
        _body->GetPosition().y <= -(Utility::PixelToMeters(Properties::WINDOW_HEIGHT)))
    {
        SetToDestroyed();
    }
}

void Laser::Init(b2World& world, b2Vec2 playerPos)
{
    
}

void Laser::Move()
{
    _body->SetLinearVelocity(_velocity);
}

void Laser::update(sf::Time elapsed)
{
    GameObject::update(elapsed);
    CheckIfOutOfScreen();
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}
