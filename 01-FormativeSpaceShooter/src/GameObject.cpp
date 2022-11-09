#include "GameObject.h"

#include <Box2D/b2_circle_shape.h>

#include "Properties.h"
#include "Utility.h"

void GameObject::createSprite(std::string path)
{
    if (!_texture.loadFromFile(path))
    {
        return;
    }

	_texture.setSmooth(true);

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);
}

void GameObject::createBody(b2World& world, b2Vec2 startPosition)
{
    // ---------------------------------------------------------------------------------------------------------
   // Body Def Init.

    b2BodyDef bodyDef;

    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    //_bodyDef.linearDamping = 1.5f;

    bodyDef.position.Set(startPosition.x / 2.0f, startPosition.y / 2.0f);

    _body = world.CreateBody(&bodyDef);

    //_body->SetUserData(this);
}

b2PolygonShape GameObject::createPolygonHitBox()
{
    b2PolygonShape hitBox;

    float spriteWidth = Utility::PixelToMeters(_sprite.getGlobalBounds().width);
    float spriteHeight = Utility::PixelToMeters(_sprite.getGlobalBounds().height);

    hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    return hitBox;
}

b2CircleShape GameObject::createCicrleHitBox()
{
    b2CircleShape hitBox;

    hitBox.m_radius = Utility::PixelToMeters(_sprite.getLocalBounds().width / 2.0f);

    return hitBox;
}

void GameObject::createFixture(b2Shape& hitBox, void* thisPtr)
{
    //_fixtureDef.shape = &hitBox;
    //_fixtureDef.density = 2.0f;
    //_fixtureDef.friction = 0.0f;
    ////FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    //_body->CreateFixture(&_fixtureDef);

    _fixtureDef.shape = &hitBox;
    _fixtureDef.density = 2.0f;
    _fixtureDef.friction = 0.0f;
    //FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);

    _fixtureDef.userData.pointer = reinterpret_cast<std::uintptr_t>(thisPtr);
    _body->CreateFixture(&_fixtureDef);
}

void GameObject::update()
{
    b2Vec2 bodyPos = _body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    // Set the position of the Graphic object
    _sprite.setPosition(graphicPosition);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(_sprite, states);
}
