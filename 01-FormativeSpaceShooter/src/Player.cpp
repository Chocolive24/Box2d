#include "core/Properties.h"
#include "core/Utility.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

// -----------------------------------------------------------------------------------------------------------------

Player::Player(Game& game) : _game(game)
{
    // -----------------------------------------------------------------------------------------------------
    // Sprite Init.

    createSprite("data/sprites/PNG/playerShip1_red.png");

    // -----------------------------------------------------------------------------------------------------
    // Body Init.

    _startPosition = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH / 2.0f,
        Properties::WINDOW_HEIGHT / 2.0f));

    createBody(_game.GetWorld(), _startPosition, b2_dynamicBody);
    _body->SetAngularDamping(0.25f);

    // -----------------------------------------------------------------------------------------------------
    // Hit box Init.

    _hitBox = createPolygonHitBox();

    // -----------------------------------------------------------------------------------------------------
    // User data Init.

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::PLAYER);

    // -----------------------------------------------------------------------------------------------------
    // Fixture Init.

    createFixture(_hitBox, 1.0f, 0.5f, 
				  (uint16)UserDataType::PLAYER, 
				  uint16(UserDataType::EDGE) | uint16(UserDataType::METEOR) | (uint16)UserDataType::EXPLOSION,
				  _userData, false);

    // -----------------------------------------------------------------------------------------------------
    // Life bar and Lives Init.

    SetCurrentLifeToMax();
}

// -----------------------------------------------------------------------------------------------------------------

void Player::Move(b2Vec2 force)
{
	_body->SetLinearVelocity(_body->GetLinearVelocity() + force);

    if (b2Abs(_body->GetLinearVelocity().Length()) < Properties::epsilonLinearVelocity) 
    {
        _body->SetLinearVelocity(b2Vec2_zero);
    }
}


// -----------------------------------------------------------------------------------------------------------------

void Player::Rotate2(float radianPerSecond)
{
    _body->SetAngularVelocity(radianPerSecond);

    if (b2Abs(_body->GetAngularVelocity()) < Properties::epsilonLinearVelocity)
    {
        _body->SetAngularVelocity(0.0f);
    }
}

// -----------------------------------------------------------------------------------------------------------------

void Player::Shoot(int level)
{
    b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);
    float width = Utility::PixelToMeters(_sprite.getGlobalBounds().width);

    const float angle = Utility::RadToDeg(_body->GetAngle());
    const b2Vec2 frontPosition = Utility::PixelsToMeters(GetFrontPosition());
    const float spread = 20.0f / 2.0f;

    for (int i = 0; i < level; i++)
    {
        float angleAfterSpread = angle - spread + 
								(spread * 2.f * static_cast<float>(i) + spread) / static_cast<float>(level);

        if (level == 1)
        {
            angleAfterSpread = angle;
        }

        _lasers.emplace_back(_game, frontPosition, angleAfterSpread);

        // Shoot the projectile here with all information
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

    // Make the player rotate to the mouse position angle.
    const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
    const auto playerPosition = _sprite.getPosition();
    const auto position = mousePosition - playerPosition;

    // Get angle between two positions
    const float angle = Utility::RadToDeg(atan2(position.y, position.x));

    Rotate(angle);

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

    for (auto& laser : _lasers)
    {
        laser.CheckIfOutOfScreen();
        laser.update(elapsed);
    }

    std::erase_if(_lasers, [](Laser& laser) { return laser.IsDestroyed(); });

    for (auto& bomb : _bombs)
    {
        bomb.update(elapsed);
    }

    std::erase_if(_bombs, [](Bomb& bomb) { return bomb.HasExploded(); });

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
}

// -----------------------------------------------------------------------------------------------------------------

sf::Vector2f Player::GetFrontPosition() const
{
    const sf::Vector2f size(_sprite.getTexture()->getSize());
    const sf::Vector2f scale = _sprite.getScale();
    const sf::Vector2f position = _sprite.getPosition();
    const float angle = _sprite.getRotation() + 90.f;

    const float x = position.x - (size.x * scale.x / 2.f) * std::cos(Utility::DegToRad(angle));
    const float y = position.y - (size.y * scale.y / 2.f) * std::sin(Utility::DegToRad(angle));

    return { x, y };
}

// -----------------------------------------------------------------------------------------------------------------

float Player::GetDeltaAngle(float angle)
{
    const float currentAngle = Utility::RadToDeg(_body->GetAngle());
    float difference = angle - currentAngle;

    while (difference < -180.f)
    {
        difference += 360.f;
    }

    while (difference > 180.f)
    {
        difference -= 360.f;
    }

    return difference + 90.f;
}

void Player::Rotate(float degreesAngle) 
{
    degreesAngle = GetDeltaAngle(degreesAngle);

    if (degreesAngle > _rotationSpeed)
    {
        degreesAngle = _rotationSpeed;
    }
    else if (degreesAngle < -_rotationSpeed)
    {
        degreesAngle = -_rotationSpeed;
    }

    _body->SetAngularVelocity(Utility::DegToRad(degreesAngle * 10.f)); // 10.f = magic number
}

// -----------------------------------------------------------------------------------------------------------------