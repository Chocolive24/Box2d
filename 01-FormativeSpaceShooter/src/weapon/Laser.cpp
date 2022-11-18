#include "core/Properties.h"
#include "core/Utility.h"
#include "weapon/Laser.h"
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

	_body->SetTransform(playerPos, Utility::DegToRad(angle));

    _velocity = b2Vec2(0.0f, 10.0f);

    b2Vec2 initialVelocity = _body->GetLocalVector(_velocity);
    _body->SetLinearVelocity(initialVelocity);

    // -----------------------------------------------------------------------------------------------------
    // Hit box Init.

    _hitBox = createPolygonHitBox();

    // -----------------------------------------------------------------------------------------------------
    // User Data Init.

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::LASER);

    // -----------------------------------------------------------------------------------------------------
    // Fixture Init.

    createFixture(_hitBox, 1.0f, 0.1f, 
				  (uint16)_userData->GetType(),
				  (uint16)UserDataType::METEOR | (uint16)UserDataType::EDGE | 
						  (uint16)UserDataType::BOMB,
				  _userData, false);

    // -----------------------------------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------------------------------------------

Laser::~Laser()
{
    _game.GetWorld().DestroyBody(_body);
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