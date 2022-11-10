#include "Meteor.h"

#include <iostream>
#include <box2d/b2_circle_shape.h>

#include "Game.h"
#include "Properties.h"
#include "Utility.h"

Meteor::Meteor(Game& game) : _game(game)
{
    createSprite("data/sprites/PNG/Meteors/meteorBrown_big1.png");

    b2Vec2 randomMeterPos = InitRndPosAndVelocity();

    createBody(_game.GetWorld(), randomMeterPos);
    b2CircleShape hitBox = createCicrleHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::METEOR);

    createFixture(hitBox, (int16)_userData->GetType(), _userData);
}

Meteor::~Meteor()
{
    _game.GetWorld().DestroyBody(_body);
}

void Meteor::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    
}

b2Vec2 Meteor::InitRndPosAndVelocity()
{
    // 1 = N, 2 = E, 3 = S, 4 = W.
    int rndCardinalPnt = Utility::GetRandomInt(1, 1);

    sf::Vector2f randomPixelPos;

    if (rndCardinalPnt == 1)
    {
        randomPixelPos = sf::Vector2f(Utility::GetRandomFloat(0.0f, Properties::WINDOW_WIDTH),
            Utility::GetRandomFloat(-50.0f, -20.0f));

        _velocity.x = 0.0f;
        _velocity.y = Utility::GetRandomFloat(-5.0f, -1.0f);
    }

    // TODO les autres point cardinaux
    // TODO rectangle shape red quand meteor detruit -> il grandit jusqu'à genre 50 pixels et fait des dégàts
    // TODO same for bomb but with 200 pixels.

    
    b2Vec2 randomMeterPos(Utility::PixelsToMeters(randomPixelPos));

    return randomMeterPos;
}

void Meteor::Move()
{
    _body->SetLinearVelocity(_body->GetLinearVelocity() + _velocity);
}

void Meteor::update(sf::Time elapsed)
{
    GameObject::update(elapsed);

    //Move();

    //// Get the position of the body
    //b2Vec2 bodyPos = _body->GetPosition();

    //// Translate meters to pixels
    //sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    //// Set the position of the Graphic object
    //_sprite.setPosition(graphicPosition);
}

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}
