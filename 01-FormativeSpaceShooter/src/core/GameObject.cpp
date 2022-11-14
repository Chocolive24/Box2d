#include <Box2D/b2_circle_shape.h>
#include "core/GameObject.h"
#include "core/Properties.h"
#include "core/Utility.h"

// -----------------------------------------------------------------------------------------------------------------

void GameObject::createSprite(std::string path)
{
    InitSprite(path);
}

// -----------------------------------------------------------------------------------------------------------------

void GameObject::createBody(b2World& world, b2Vec2 startPosition, b2BodyType type)
{
    b2BodyDef bodyDef;

    bodyDef.fixedRotation = true;
    bodyDef.type = type;
    //_bodyDef.linearDamping = 1.5f;

    bodyDef.position.Set(startPosition.x, startPosition.y);

    _body = world.CreateBody(&bodyDef);
}

// -----------------------------------------------------------------------------------------------------------------

b2PolygonShape GameObject::createPolygonHitBox()
{
    b2PolygonShape hitBox;

    float spriteWidth = Utility::PixelToMeters(_sprite.getGlobalBounds().width);
    float spriteHeight = Utility::PixelToMeters(_sprite.getGlobalBounds().height);

    hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    return hitBox;
}

// -----------------------------------------------------------------------------------------------------------------

b2CircleShape GameObject::createCicrleHitBox()
{
    b2CircleShape hitBox;

    // Radius = 90% of the half width of the sprite.
    hitBox.m_radius = Utility::PixelToMeters((_sprite.getLocalBounds().width / 2.0f) * 0.95f);
    
    return hitBox;
}

// -----------------------------------------------------------------------------------------------------------------

void GameObject::createFixture(b2Shape& hitBox, int16 userDataIndex, UserData* userData, bool isSensor)
{
    _fixtureDef.shape = &hitBox;
    _fixtureDef.density = 2.0f;
    _fixtureDef.friction = 0.0f;
    _fixtureDef.isSensor = isSensor;

    if(!_addedToGroupIndex)
    {
        _fixtureDef.filter.groupIndex = userDataIndex;
        _addedToGroupIndex = true;
    }

    _fixtureDef.userData.pointer = reinterpret_cast<std::uintptr_t>(userData);
    _body->CreateFixture(&_fixtureDef);
}

// -----------------------------------------------------------------------------------------------------------------

void GameObject::update(sf::Time elapsed)
{
    //_totalElapsed += elapsed;

    b2Vec2 bodyPos = _body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    // Set the position of the Graphic object
    _sprite.setPosition(graphicPosition);
}

// -----------------------------------------------------------------------------------------------------------------

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableObject::draw(target, states);
}

// -----------------------------------------------------------------------------------------------------------------