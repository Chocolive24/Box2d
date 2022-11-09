#include "Bomb.h"

#include <iostream>
#include <Box2D/b2_circle_shape.h>

#include "Properties.h"
#include "Utility.h"

void Bomb::Init(b2World& world, b2Vec2 playerPos)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    createSprite("data/sprites/PNG/Lasers/laserRed08.png");
    createBody(world, playerPos);
    b2CircleShape hitBox = createCicrleHitBox();
    _userData->SetType(UserDataType::BOMB);
    createFixture(hitBox, (int)_userData->GetType());

    std::cout << hitBox.m_radius;

    if (!_buffer.loadFromFile("data/sound/bomb.wav"))
    {
        return;
    }

    _sound.setBuffer(_buffer);

}

void Bomb::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter(force, true);
}

void Bomb::update()
{
    GameObject::update();

    /*if (Properties::TOTALELAPSED.asMilliseconds() >= Properties::BOMBMOVEMENT)
    {
        Move(b2Vec2(0, 0));
    }*/
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

