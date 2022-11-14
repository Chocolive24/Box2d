#include "core/Properties.h"
#include "core/Utility.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

// -----------------------------------------------------------------------------------------------------------------

Player::Player(Game& game) : _game(game), _bombExplosion(_game)
{
    // -----------------------------------------------------------------------------------------------------
    // Shape Init.

    createSprite("data/sprites/PNG/playerShip1_red.png");

    // -----------------------------------------------------------------------------------------------------
    // Body Init.

    _startPosition = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH / 2.0f,
        Properties::WINDOW_HEIGHT / 2.0f));

    createBody(_game.GetWorld(), _startPosition, b2_dynamicBody);

    // -----------------------------------------------------------------------------------------------------
    // Hit box Init.

    _hitBox = createPolygonHitBox();

    // -----------------------------------------------------------------------------------------------------
    // User data Init.

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::PLAYER);

    // -----------------------------------------------------------------------------------------------------
    // Fixture Init.

    createFixture(_hitBox, (int16)_userData->GetType(), _userData, true);

    // -----------------------------------------------------------------------------------------------------
    // Life bar and Lives Init.

    SetCurrentLifeToMax();
}

// -----------------------------------------------------------------------------------------------------------------

void Player::Move(b2Vec2 force)
{
    _body->SetLinearVelocity(_body->GetLinearVelocity() + force);
}

// -----------------------------------------------------------------------------------------------------------------

void Player::Rotate(float omega)
{
    _body->SetAngularVelocity(omega);
    _body->ApplyTorque(omega, true);
    _body->SetTransform(_body->GetPosition(), _body->GetAngle());
    
    _sprite.rotate(_body->GetAngle());
}

// -----------------------------------------------------------------------------------------------------------------

void Player::Shoot(int level)
{
    b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);
    float width = Utility::PixelToMeters(_sprite.getGlobalBounds().width);

    if (level == 1)
    {
        AddLaserLvl1(width);
    }

    if (level == 2)
    {
        AddLaserLvl2(width);
    }

    else if (level == 3)
    {
        AddLaserLvl3(width);
    }

    else if (level == 4)
    {
        AddLaserLvl4(width);
    }

    else if (level == 5)
    {
        AddLaserLvl5(width);
    }

    _canShoot = false;
}

// -----------------------------------------------------------------------------------------------------------------

void Player::ThrowBomb(b2World& world)
{
    if (_bombNbr > 0)
    {
        b2Vec2 startPos(_body->GetPosition().x, (_body->GetPosition().y + 0.8f));
        
        _bombs.emplace_back(_game, startPos);

        _bombs.back().Move();

        _bombNbr -= 1;
    }
}

// -----------------------------------------------------------------------------------------------------------------

void Player::update(sf::Time elapsed)
{
    // -----------------------------------------------------------------------------------------------------
    // Update the player's sprite.

    GameObject::update(elapsed);

    // -----------------------------------------------------------------------------------------------------
	// Update the player's data.

    if (GetCurrentLife() <= 0)
    {
        _currentLife = 0;
    }

    // -----------------------------------------------------------------------------------------------------
    // Update the player's attacks.

    _lastShotDuration += elapsed;

    if (_lastShotDuration.asSeconds() >= Properties::LASER_COOLDOWN)
    {
        _canShoot = true;
        _lastShotDuration = sf::Time::Zero;
    }

    std::erase_if(_lasers, [](Laser& laser) { return laser.IsDestroyed(); });

    for (auto& laser : _lasers)
    {
        laser.CheckIfOutOfScreen();
        laser.update(elapsed);
    }

    for (auto& bomb : _bombs)
    {
        bomb.update(elapsed);

        if (bomb.IsDestroyed())
        {
            _bombExplosion.Init(_game, bomb.GetBody()->GetPosition());
            _bombExplosion.CreateAnExplosion();
        }
    }

    if (_bombExplosion.IsAnExplosion())
    {
        _bombExplosion.update(elapsed);
    }

    std::erase_if(_bombs, [](Bomb& bomb) { return bomb.IsDestroyed(); });

    // -----------------------------------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------------------------------------------

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);

    for (auto& laser : _lasers)
    {
        target.draw(laser);
    }
    for (auto& bomb : _bombs)
    {
        target.draw(bomb);
    }

    target.draw(_bombExplosion);
}

// -----------------------------------------------------------------------------------------------------------------

void Player::AddLaserLvl1(float spriteWidth)
{
    b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);
    _lasers.emplace_back(_game, startPos, _body->GetAngle());
    _lasers.back().Move();
    _lasers.back().SetAngle(_body->GetAngle());
}

// -----------------------------------------------------------------------------------------------------------------

void Player::AddLaserLvl2(float spriteWidth)
{
    for (int i = 0; i < 2; i++)
    {
        b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);
        spriteWidth *= -1;
        startPos.x += spriteWidth / 4.0f;
        _lasers.emplace_back(_game, startPos, _body->GetAngle());
        _lasers.back().Move();
    }
}

// -----------------------------------------------------------------------------------------------------------------

void Player::AddLaserLvl3(float spriteWidth)
{
    AddLaserLvl2(spriteWidth);
    AddLaserLvl1(spriteWidth);
}

// -----------------------------------------------------------------------------------------------------------------

void Player::AddLaserLvl4(float spriteWidth)
{
    for (int i = 1; i <= 4; i++)
    {
        b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);

        if (i < 3)
        {
            _lasers.emplace_back(_game, b2Vec2(startPos.x - i * spriteWidth / 6.0f, startPos.y),
                _body->GetAngle());
        }

        else
        {
            _lasers.emplace_back(_game, b2Vec2(startPos.x + i / 2 * spriteWidth / 6.0f, startPos.y),
                _body->GetAngle());
        }

        _lasers.back().Move();
    }
}

// -----------------------------------------------------------------------------------------------------------------

void Player::AddLaserLvl5(float spriteWidth)
{
    b2Vec2 startPos(_body->GetPosition().x - spriteWidth / 2.0f, _body->GetPosition().y + 0.6f);

    for (int i = 1; i < 6; i++)
    {
        _lasers.emplace_back(_game, b2Vec2(startPos.x + i * spriteWidth / 5.0f, startPos.y),
            _body->GetAngle());

        _lasers.back().Move();
    }
}

// -----------------------------------------------------------------------------------------------------------------