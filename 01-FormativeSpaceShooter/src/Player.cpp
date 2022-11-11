#include "Player.h"

#include <iostream>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Player::Player(Game& game) : _game(game)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    createSprite("data/sprites/PNG/playerShip1_red.png");

    // ---------------------------------------------------------------------------------------------------------
    // Body Init.

    _startPosition = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH / 2.0f,
        Properties::WINDOW_HEIGHT / 2.0f));

    createBody(_game.GetWorld(), _startPosition);

    // ---------------------------------------------------------------------------------------------------------
    // Hit box Init.

    _hitBox = createPolygonHitBox();

    // ---------------------------------------------------------------------------------------------------------
    // User data Init.

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::PLAYER);

    // ---------------------------------------------------------------------------------------------------------
    // Fixture Init.

    createFixture(_hitBox, (int16)_userData->GetType(), _userData);

    // ---------------------------------------------------------------------------------------------------------
    // Life bar and Lives Init.

    SetCurrentLifeToMax();
}

void Player::Init(b2World& world)
{
    if (!_fireTexture.loadFromFile("data/sprites/PNG/Effects/fire07.png"))
    {
        return;
    }

    _fireTexture.setSmooth(true);

    _fireSprite.setTexture(_fireTexture);
    _fireSprite.setOrigin(_fireSprite.getGlobalBounds().width / 2.0f, _fireSprite.getGlobalBounds().height / 2.0f);
}

void Player::InitLifeBar()
{

}

void Player::InitLives()
{
    
}

void Player::Move(b2Vec2 force)
{
    _body->SetLinearVelocity(_body->GetLinearVelocity() + force);
}

void Player::Rotate(float omega)
{
    _body->SetAngularVelocity(omega);
    _body->ApplyTorque(_body->GetAngle(), true);
    _body->SetTransform(_body->GetPosition(), _body->GetAngle());
    
    _sprite.rotate(_body->GetAngle());
}

void Player::AddLaser(b2World& world)
{
    
}

void Player::Shoot(b2World& world)
{
    b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 0.6f);

    _lasers.emplace_back(_game, startPos);

    _lasers.back().Move(_lasers.back().GetVelocity());
    _lasers.back().SetAngle(_body->GetAngle());

    _canShoot = false;
}

void Player::ThrowBomb(b2World& world)
{
    if (_bombNbr > 0)
    {
        b2Vec2 startPos(_body->GetPosition().x, (_body->GetPosition().y + 0.8f));
        
        _bombs.emplace_back(_game, startPos);

        _bombs.back().Move(b2Vec2(0, 50));

        _bombNbr -= 1;
    }
}

void Player::update(sf::Time elapsed)
{
    // -------------------------------------------------------------------------------------------------------------
    // Update the ship.

    GameObject::update(elapsed);

    _lastShotDuration += elapsed;

    if (_lastShotDuration.asSeconds() >= Properties::LASER_COOLDOWN)
    {
        _canShoot = true;
        _lastShotDuration = sf::Time::Zero;
    }

	// -------------------------------------------------------------------------------------------------------------
	// Update the player's data.

    // -------------------------------------------------------------------------------------------------------------
    // Update the player's attacks.

    std::erase_if(_lasers, [](Laser& laser) { return laser.IsDestroyed(); });

    for (auto& laser : _lasers)
    {
        laser.CheckIfOutOfScreen();
        laser.update(elapsed);
    }

    std::erase_if(_bombs, [](Bomb& bomb) { return bomb.IsDestroyed(); });

    for (auto& bomb : _bombs)
    {
        bomb.update(elapsed);
    }

    // -------------------------------------------------------------------------------------------------------------
    // Tests.

   /* std::cout << _hitBox.m_vertices->x << " " << _hitBox.m_vertices->y << std::endl;
    std::cout << _shipSprite.getGlobalBounds().width << " " << _shipSprite.getGlobalBounds().height << std::endl;*/

    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
    //std::cout << _body->GetAngularVelocity() << std::endl;

    /*std::cout << "body position [" << _body->GetPosition().x << ":" << _body->GetPosition().y
        << "]|shape position [" << _shipSprite.getPosition().x << ":" << _shipSprite.getPosition().y << "]" << std::endl;*/
    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
}

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
