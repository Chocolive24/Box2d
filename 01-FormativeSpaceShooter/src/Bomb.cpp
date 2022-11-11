#include "Bomb.h"

#include <iostream>
#include <Box2D/b2_circle_shape.h>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Bomb::Bomb(Game& game, b2Vec2 playerPos) : _game(game)
{
    createSprite("data/sprites/PNG/Lasers/laserRed08.png");

    

    createBody(_game.GetWorld(), playerPos);
    b2CircleShape hitBox = createCicrleHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::BOMB);

    createFixture(hitBox, (int16)_userData->GetType(), _userData);
}

Bomb::~Bomb()
{
    _game.GetWorld().DestroyBody(_body);
}

void Bomb::Init(b2World& world, b2Vec2 playerPos)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.
}

void Bomb::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter(force, true);
}

void Bomb::update(sf::Time elapsed)
{
    GameObject::update(elapsed);

    /*if (Properties::TOTALELAPSED.asMilliseconds() >= Properties::BOMBMOVEMENT)
    {
        Move(b2Vec2(0, 0));
    }*/
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}

