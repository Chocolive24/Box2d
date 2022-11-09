#include "Meteor.h"

#include <iostream>

#include "Properties.h"
#include "Utility.h"

void Meteor::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    createSprite("data/sprites/PNG/Meteors/meteorBrown_big1.png");

    sf::Vector2f randomPixelPos(Utility::GetRandomFloat(0.0f, Properties::WINDOW_WIDTH),
								Utility::GetRandomFloat(0.0f, Properties::WINDOW_HEIGHT));
    b2Vec2 randomMeterPos(Utility::PixelsToMeters(randomPixelPos));

    std::cout << randomMeterPos.x << " " << randomMeterPos.y << std::endl;

    createBody(world, randomMeterPos);
    b2PolygonShape hitBox = createPolygonHitBox();
    _userData->SetType(UserDataType::METEOR);
    createFixture(hitBox, (int)_userData->GetType());

    /*if (!_texture.loadFromFile("data/sprites/PNG/Meteors/meteorBrown_big1.png"))
    {
        return;
    }*/

    //_texture.setSmooth(true);

    //_sprite.setTexture(_texture);
    //_sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);

    //// ---------------------------------------------------------------------------------------------------------
    //// Body Def Init.

    //_bodyDef.fixedRotation = true;
    //_bodyDef.type = b2_dynamicBody;
    ////_bodyDef.linearDamping = 1.5f;

    //sf::Vector2f randomPixelPos(Utility::GetRandomNumber<float>(0.0f, Properties::WINDOW_WIDTH),
    //    Utility::GetRandomNumber<float>(0.0f, Properties::WINDOW_HEIGHT));

    //b2Vec2 randomMeterPos(Utility::PixelsToMeters(randomPixelPos));

    //_bodyDef.position.Set(randomMeterPos.x, randomMeterPos.y);

    //_body = world.CreateBody(&_bodyDef);

    //// ---------------------------------------------------------------------------------------------------------
    //// Physical shape Init.

    //float spriteWidth = Utility::PixelToMeters(_sprite.getGlobalBounds().width);
    //float spriteHeight = Utility::PixelToMeters(_sprite.getGlobalBounds().height);

    //_hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    //// ---------------------------------------------------------------------------------------------------------
    //// Fixture Init.

    //FixtureDef.shape = &_hitBox;
    //FixtureDef.density = 2.0f;
    //FixtureDef.friction = 0.0f;
    ////FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    //_body->CreateFixture(&FixtureDef);

    if (!_buffer.loadFromFile("data/sound/sfx_laser2.wav"))
    {
        return;
    }

    _sound.setBuffer(_buffer);

    _velocity.x = Utility::GetRandomFloat(0.1f, 3);
    _velocity.y = Utility::GetRandomFloat(0.1f, 3);
}

void Meteor::Move()
{
    _body->ApplyForceToCenter(_velocity, true);
}

void Meteor::update()
{
    GameObject::update();

    Move();

    //// Get the position of the body
    //b2Vec2 bodyPos = _body->GetPosition();

    //// Translate meters to pixels
    //sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    //// Set the position of the Graphic object
    //_sprite.setPosition(graphicPosition);
}

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
