
#include <iostream>

#include "core/SFML_Utilities.h"
#include "core/userData.h"
#include "managers/textureManager.h"

#include "game.h"
#include "ship.h"

Ship::Ship(b2World& world_) : Box2DEntity(world_)
{
    createFixture(pixelsToMeters(texManager->getShipTexture().getSize().x), pixelsToMeters(texManager->getShipTexture().getSize().y));
}

void Ship::init(sf::Vector2u winsize) {

    // Defining the shape
    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getShipTexture());
    m_sprite.setOrigin(texManager->getShipTexture().getSize().x * 0.5f, texManager->getShipTexture().getSize().y * 0.5f);
    
    // Set Datas
    //m_userData->setLocalId(-1);
    m_userData->setType(UserDataType::SHIP);
    
    m_body->SetLinearDamping(0.5f);
    m_body->SetAngularDamping(0.25f);

}

void Ship::createFixture(const float sizeX, const float sizeY) {

    // Shape of the physical (A box)
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * sizeX, 0.5f * sizeY);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userData);
	m_body->CreateFixture(&playerFixtureDef);

}

float Ship::getLife()
{
    return m_life;
}

void Ship::setDamages(float damages_)
{
    m_life -= damages_;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Ship::update()
{
    Box2DEntity::update();

    if (b2Abs(m_body->GetLinearVelocity().Length()) < epsilonLinearVelocity) {
        m_body->SetLinearVelocity(b2Vec2_zero);
    }

}

void Ship::move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity) {

    b2Vec2 pos = pixelsToMeters(_pixelsPosition);
    b2Vec2 vel = pixelsToMeters(_velocity);

    m_body->SetTransform(pos, 0.0f);

}

void Ship::speedUp(float forceValue) {
    ApplyLocalForceWithCheck(1.0f * forceValue);
}

void Ship::ApplyLocalForceWithCheck(float forceValue) {

    b2Vec2 force(0.0, forceValue);
    b2Vec2 localForce = m_body->GetWorldVector(force);

    m_body->SetLinearDamping(0.5f);

    //ApplyLocalForceWithCheck(1.0f * forceValue);
    if (m_body->GetLinearVelocity().Length() < maxLinearVelocity) {
        m_body->ApplyForceToCenter(localForce, true);
    }

        if (b2Abs(m_body->GetLinearVelocity().Length()) < epsilon) {
            m_body->SetLinearVelocity(b2Vec2_zero);
        }
    }

void Ship::speedDown(float forceValue)
{
	m_body->SetLinearDamping(forceValue);
}

void Ship::rotateLeft(float torque)
{
    ApplyTorqueWithCheck(1.0f * torque);
}

void Ship::rotateRight(float torque) {
    ApplyTorqueWithCheck(-1.0f * torque);
}

void Ship::ApplyTorqueWithCheck(float torque) {

    setAngularDamping(0.5f);


    if ((torque > 0 && m_body->GetAngularVelocity() < maxAngularVelocity) || (torque < 0 && m_body->GetAngularVelocity() > -1.0 * maxAngularVelocity)) {

        m_body->ApplyTorque(torque, true);

        if (b2Abs(m_body->GetAngularVelocity()) < epsilonAngularVelocity) {
            m_body->SetAngularVelocity(0.0f);
        }

    }

}

void Ship::setAngularDamping(float dampingValue)
{
    m_body->SetAngularDamping(dampingValue);
}

