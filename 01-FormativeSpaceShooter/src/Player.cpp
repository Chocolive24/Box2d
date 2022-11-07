#include "Player.h"

#include <iostream>

#include "Properties.h"
#include "Utility.h"

void Player::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    if (!_texture.loadFromFile("data/sprites/PNG/playerShip1_red.png"))
    {
        return;
    }

    _texture.setSmooth(true);

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);

    //_sprite.setScale(0.8f, 0.8f);

    // ---------------------------------------------------------------------------------------------------------
    // Body Def Init.

    _bodyDef.fixedRotation = false;
    _bodyDef.type = b2_dynamicBody;
    //_bodyDef.linearDamping = 1.5f;
    b2Vec2 windowSize(Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH, 
														   Properties::WINDOW_HEIGHT)));
    _bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);

    _body = world.CreateBody(&_bodyDef);

    // ---------------------------------------------------------------------------------------------------------
    // Physical shape Init.

    float spriteWidth  = Utility::PixelToMeters(_sprite.getGlobalBounds().width);
    float spriteHeight = Utility::PixelToMeters(_sprite.getGlobalBounds().height);

    _hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Fixture Init.

    _playerFixtureDef.shape = &_hitBox;
    _playerFixtureDef.density = 2.0f;
    _playerFixtureDef.friction = 0.0f;
    //FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    _body->CreateFixture(&_playerFixtureDef);

    InitLifeBar();
}

void Player::InitLifeBar()
{
    _currentLife = _maxLife;

    _currentLifeBar.setFillColor(sf::Color::Green);

    _currentLifeBar.setSize(sf::Vector2f(2 * _currentLife, 20));
    _currentLifeBar.setPosition(12, 15);

    _damagedLifeBar.setFillColor(sf::Color::Red);
    _damagedLifeBar.setOutlineThickness(2.0f);
    _damagedLifeBar.setOutlineColor(sf::Color::Black);

    _damagedLifeBar.setSize(sf::Vector2f(2 * _maxLife, 20));
    _damagedLifeBar.setPosition(12, 15);
}

void Player::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter((force), true);
}

void Player::Rotate(float omega)
{
    _body->ApplyTorque(omega, true);
    _body->SetTransform(_body->GetPosition(), 1.0f);
    _sprite.rotate(2.0f);
}

void Player::AddLaser(b2World& world)
{
    
}

void Player::Shoot(b2World& world)
{
    Laser* laser = new Laser;
    laser->Init(world, _body->GetPosition());
    _lasers.emplace_back(laser);

    laser->PlaySound();

	laser->Move(b2Vec2(0, 50));
}

void Player::Update()
{
    // Get the position of the body
    b2Vec2 bodyPos = _body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    // Set the position of the Graphic object
    _sprite.setPosition(graphicPosition);



    /*std::cout << _hitBox.m_vertices->x << " " << _hitBox.m_vertices->y << std::endl;
    std::cout << _sprite.getGlobalBounds().width << " " << _sprite.getGlobalBounds().height << std::endl;*/

    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
    //std::cout << _body->GetAngularVelocity() << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(_sprite, states);
    target.draw(_damagedLifeBar);
    target.draw(_currentLifeBar, states);
}
