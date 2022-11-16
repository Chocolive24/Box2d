#include "Meteor.h"

#include <iostream>
#include <box2d/b2_circle_shape.h>

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

Meteor::Meteor(Game& game) : _game(game)
{
    createSprite("data/sprites/PNG/Meteors/meteorBrown_big1.png");

    b2Vec2 randomMeterPos = InitRndPosAndVelocity();

    createBody(_game.GetWorld(), randomMeterPos, b2_dynamicBody);
    b2CircleShape hitBox = createCicrleHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::METEOR);

    createFixture(hitBox, 2.0f, 0.5f,
				  (uint16)UserDataType::METEOR,
				  (uint16)UserDataType::METEOR | (uint16)UserDataType::PLAYER |
				  (uint16)UserDataType::LASER | (uint16)UserDataType::BOMB | (uint16)UserDataType::EXPLOSION,
				  _userData, false);
}

Meteor::~Meteor()
{
    _game.GetWorld().DestroyBody(_body);
}

b2Vec2 Meteor::InitRndPosAndVelocity()
{
    // 1 = North, 2 = East, 3 = South, 4 = West.
    int rndCardinalPnt = Utility::GetRandomInt(1, 4);

    sf::Vector2f randomPixelPos;

    // Meteor appear from the North of the screen.
    if (rndCardinalPnt == 1)
    {
        randomPixelPos = sf::Vector2f(Utility::GetRandomFloat(50.0f, Properties::WINDOW_WIDTH - 50.0f),
            Utility::GetRandomFloat(-50.0f, -20.0f));

        if (randomPixelPos.x <= Properties::WINDOW_WIDTH / 2.0f)
        {
            _velocity.x = Utility::GetRandomFloat(0.0f, 2.0f);
        }

        else
        {
            _velocity.x = Utility::GetRandomFloat(-2.0f, 0.0f);
        }

        _velocity.y = Utility::GetRandomFloat(-5.0f, -1.0f);
    }

    // Meteor appear from the East of the screen.
    else if (rndCardinalPnt == 2)
    {
        randomPixelPos = sf::Vector2f(Utility::GetRandomFloat(
				Properties::WINDOW_WIDTH + 20, Properties::WINDOW_WIDTH + 50),
                Utility::GetRandomFloat(50.0f, Properties::WINDOW_HEIGHT - 50.0f));

        if (randomPixelPos.y <= Properties::WINDOW_HEIGHT / 2.0f)
        {
            _velocity.y = Utility::GetRandomFloat(0.0f, 2.0f);
        }

        else
        {
            _velocity.y = Utility::GetRandomFloat(-2.0f, 0.0f);
        }

        _velocity.x = Utility::GetRandomFloat(-7.5f, -2.5f);
    }

    // Meteor appear from the South of the screen.
    else if (rndCardinalPnt == 3)
    {
        randomPixelPos = sf::Vector2f(Utility::GetRandomFloat(50.0f, Properties::WINDOW_WIDTH - 50),
            Utility::GetRandomFloat(Properties::WINDOW_HEIGHT + 20.0f, Properties::WINDOW_HEIGHT + 50.0f));

        if (randomPixelPos.x <= Properties::WINDOW_WIDTH / 2.0f)
        {
            _velocity.x = Utility::GetRandomFloat(0.0f, 2.0f);
        }

        else
        {
            _velocity.x = Utility::GetRandomFloat(-2.0f, 0.0f);
        }

        _velocity.y = Utility::GetRandomFloat(1.5f, 5.0f);
    }

    // Meteor appear from the West of the screen.
    else if (rndCardinalPnt == 4)
    {
        randomPixelPos = sf::Vector2f(Utility::GetRandomFloat(-50, -20),
            Utility::GetRandomFloat(50.0f, Properties::WINDOW_HEIGHT - 50.0f));

        if (randomPixelPos.y <= Properties::WINDOW_HEIGHT / 2.0f)
        {
            _velocity.y = Utility::GetRandomFloat(0.0f, 2.0f);
        }

        else
        {
            _velocity.y = Utility::GetRandomFloat(-2.0f, 0.0f);
        }

        _velocity.x = Utility::GetRandomFloat(2.5f, 7.5f);
    }


    // TODO les autres point cardinaux
    // TODO rectangle shape red quand meteor detruit -> il grandit jusqu'à genre 50 pixels et fait des dégàts
    // TODO same for bomb but with 200 pixels.

    b2Vec2 randomMeterPos(Utility::PixelsToMeters(randomPixelPos));

    return randomMeterPos;
}

void Meteor::Move()
{
    _body->SetLinearVelocity(_velocity);
}

void Meteor::update(sf::Time elapsed)
{
    GameObject::update(elapsed);

    if (_body->GetPosition().x < Utility::PixelToMeters(-60.0f) ||
        _body->GetPosition().x > Utility::PixelToMeters(Properties::WINDOW_WIDTH + 60) ||
        _body->GetPosition().y > -(Utility::PixelToMeters(-60.0f)) ||
        _body->GetPosition().y < -(Utility::PixelToMeters(Properties::WINDOW_HEIGHT + 60)))
    {
        SetToDestroyed();
        std::cout << "IL EST MORT" << std::endl;
    }
}

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}
