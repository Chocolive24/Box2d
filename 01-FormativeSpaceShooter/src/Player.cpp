#include "Player.h"

#include <iostream>

void Player::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    _shape.setSize(sf::Vector2f(100.0f, 100.0f));
    _shape.setFillColor(sf::Color::Red);
    _shape.setOrigin(_shape.getGlobalBounds().width / 2.0f, _shape.getGlobalBounds().height / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Body Def Init.

    _bodyDef.fixedRotation = true;
    _bodyDef.type = b2_dynamicBody;
    _bodyDef.linearDamping = 1.5f;
    //b2Vec2 windowSize(window.getSize().x / pixelMetersRatio, window.getSize().y / pixelMetersRatio);
    _bodyDef.position.Set(8, 0);

    _body = world.CreateBody(&_bodyDef);

    // ---------------------------------------------------------------------------------------------------------
    // Physical shape Init.

    _box.SetAsBox(_shape.getSize().x / _pixelMetersRatio, _shape.getSize().y / _pixelMetersRatio);

    // ---------------------------------------------------------------------------------------------------------
    // Fixture Init.

    _playerFixtureDef.shape = &_box;
    _playerFixtureDef.density = 1.0f;
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
    sf::Vector2f graphicPosition(bodyPos.x * _pixelMetersRatio, -bodyPos.y * _pixelMetersRatio);
    // Set the position of the Graphic object
    _shape.setPosition(graphicPosition);

    std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shape, states);
}
