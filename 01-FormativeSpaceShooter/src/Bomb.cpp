#include "Bomb.h"

#include "Properties.h"
#include "Utility.h"

void Bomb::Init(b2World& world, b2Vec2 playerPos)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    if (!_texture.loadFromFile("data/sprites/PNG/Lasers/laserRed08.png"))
    {
        return;
    }

    _texture.setSmooth(true);

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Body Def Init.

    _bodyDef.fixedRotation = true;
    _bodyDef.type = b2_dynamicBody;
    //_bodyDef.linearDamping = 1.5f;
    b2Vec2 windowSize(Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH,
        Properties::WINDOW_HEIGHT)));
    _bodyDef.position.Set(playerPos.x, playerPos.y + 1.0f);

    _body = world.CreateBody(&_bodyDef);

    // ---------------------------------------------------------------------------------------------------------
    // Physical shape Init.

    float spriteWidth = Utility::PixelToMeters(_sprite.getGlobalBounds().width);
    float spriteHeight = Utility::PixelToMeters(_sprite.getGlobalBounds().height);

    _hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
    // Fixture Init.

    FixtureDef.shape = &_hitBox;
    FixtureDef.density = 2.0f;
    FixtureDef.friction = 0.0f;
    //FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    _body->CreateFixture(&FixtureDef);

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

void Bomb::Update()
{
    // Get the position of the body
    b2Vec2 bodyPos = _body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    // Set the position of the Graphic object
    _sprite.setPosition(graphicPosition);

    

    /*if (Properties::TOTALELAPSED.asMilliseconds() >= Properties::BOMBMOVEMENT)
    {
        Move(b2Vec2(0, 0));
    }*/
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
