
#include <iostream>

#include "bouncer.h"
#include "game.h"
#include "core/SFML_Utilities.h"

Bouncer::Bouncer(b2World& world_, sf::Vector2f pos_, sf::Vector2f size_) : Box2DEntity(world_)
{

    createFixture(pixelsToMeters(size_.x), pixelsToMeters(size_.y));

	// Set Datas
    m_userData->setLocalId(-1);
    m_userData->setType(UserDataType::LIMIT);

    m_body->SetTransform(pixelsToMeters(pos_), 0);
    m_body->SetType(b2BodyType::b2_staticBody);

}

void Bouncer::createFixture(const float sizeX, const float sizeY)
{
    m_body->DestroyFixture(m_body->GetFixtureList());
    // The fixture is what it defines the physic react
    b2PolygonShape bouncerBox;
    bouncerBox.SetAsBox(sizeX, sizeY);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &bouncerBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.2f;
    playerFixtureDef.restitution = 0.01f; // Make it bounce a little bit

    m_body->CreateFixture(&playerFixtureDef);

}

    
//void Bouncer::update() {
//
//    const auto& b2Position = m_body->GetPosition();
//    m_shape.setPosition(metersToPixels(b2Position));
//    const auto b2rotation = m_body->GetAngle();
//    m_shape.setRotation(-1.0f * radToDeg(b2rotation));
//    
//}

void Bouncer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    //target.draw(m_shape, states);
}

