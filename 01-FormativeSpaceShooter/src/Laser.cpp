#include "core/Properties.h"
#include "core/Utility.h"
#include "Laser.h"
#include "Game.h"

#include <iostream>

// -----------------------------------------------------------------------------------------------------------------

Laser::Laser(Game& game, b2Vec2 playerPos, float angle) : _game(game)
{
    // -----------------------------------------------------------------------------------------------------
    // Sprite Init.

    createSprite("data/sprites/PNG/Lasers/laserRed01.png");

    // -----------------------------------------------------------------------------------------------------
    // Body Init.

    createBody(_game.GetWorld(), playerPos, b2_kinematicBody);
    _body->SetTransform(playerPos, angle * 3.14f / 180.0f - 90);

    // -----------------------------------------------------------------------------------------------------
    // Hit box Init.

    _hitBox = createPolygonHitBox();

    // -----------------------------------------------------------------------------------------------------
    // User Data Init.

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::LASER);

    // -----------------------------------------------------------------------------------------------------
    // Fixture Init.

    createFixture(_hitBox, (int16)_userData->GetType(), _userData, true);

    // -----------------------------------------------------------------------------------------------------
    // Velocity Init.
    _velocity = b2Vec2(0.0f, 10.0f);

    // -----------------------------------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------------------------------------------

Laser::~Laser()
{
    _game.GetWorld().DestroyBody(_body);
    std::cout << _isDestroyed << std::endl;
}

// -----------------------------------------------------------------------------------------------------------------

void Laser::CheckIfOutOfScreen()
{
    if (_body->GetPosition().y >= 0 || 
        _body->GetPosition().y <= -(Utility::PixelToMeters(Properties::WINDOW_HEIGHT)))
    {
        SetToDestroyed();
    }
}

// -----------------------------------------------------------------------------------------------------------------

void Laser::Move()
{
    _body->SetLinearVelocity(_velocity);
}

// -----------------------------------------------------------------------------------------------------------------

void Laser::update(sf::Time elapsed)
{
    GameObject::update(elapsed);
    CheckIfOutOfScreen();
}

// -----------------------------------------------------------------------------------------------------------------

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}

// -----------------------------------------------------------------------------------------------------------------