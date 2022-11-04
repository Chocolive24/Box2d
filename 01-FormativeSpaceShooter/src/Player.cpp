#include "Player.h"

#include <iostream>

#include "Properties.h"
#include "Utility.h"

void Player::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    /*_shape.setSize(sf::Vector2f(100.0f, 100.0f));
    _shape.setFillColor(sf::Color::Red);
    _shape.setOrigin(_shape.getGlobalBounds().width / 2.0f, _shape.getGlobalBounds().height / 2.0f);*/

    if (!_texture.loadFromFile("data/sprites/PNG/playerShip1_red.png"))
    {
        return;
    }

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Body Def Init.

    _bodyDef.fixedRotation = true;
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

    _box.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Fixture Init.

    _playerFixtureDef.shape = &_box;
    _playerFixtureDef.density = 2.0f;
    _playerFixtureDef.friction = 0.0f;
    //_playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    _body->CreateFixture(&_playerFixtureDef);
}

void Player::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter((force), true);
}

void Player::Update()
{
    // Get the position of the body
    b2Vec2 bodyPos = _body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    // Set the position of the Graphic object
    _sprite.setPosition(graphicPosition);

    /*std::cout << _box.m_vertices->x << " " << _box.m_vertices->y << std::endl;
    std::cout << _sprite.getGlobalBounds().width << " " << _sprite.getGlobalBounds().height << std::endl;*/

    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
