#include "core/box2DEntity.h"

Box2DEntity::Box2DEntity(b2World& world_) : m_world(world_){

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;
    m_userData = new UserData();
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
    m_body = m_world.CreateBody(&bodyDef);

    // Set angle and velocity
    m_body->SetTransform(b2Vec2(0,0), 0);
    m_body->SetLinearVelocity(b2Vec2(0, 0));

    //m_body->SetTransform(startPos_, angle_);
    //m_body->SetLinearVelocity(velocity_);

}

Box2DEntity::~Box2DEntity()
{
    m_world.DestroyBody(m_body);
}

void Box2DEntity::update()
{

    // Get the position of the body
    b2Vec2 bodyPos = m_body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = m_body->GetAngle();
    setRotation(-1 * radToDeg(angle));

}



//void Box2DEntity::createFixture(const b2Vec2 size_)
//{
//
//	// Shape of the physical (A box)
//    b2CircleShape hitBox;
//    hitBox.m_radius = pixelsToMeters(size_.x * 0.5f);
//
//    // The fixture is what it defines the physic react
//    b2FixtureDef playerFixtureDef;
//    playerFixtureDef.shape = &hitBox;
//    playerFixtureDef.density = 1.0f;
//    playerFixtureDef.friction = 0.0f;
//    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
//    m_body->CreateFixture(&playerFixtureDef);
//
//}

