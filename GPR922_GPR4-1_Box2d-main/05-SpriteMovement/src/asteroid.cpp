#include "asteroid.h"

long Asteroid::m_localIdAsteroid = 0;

Asteroid::Asteroid(b2World& world_, sf::Vector2f size_) : Box2DEntity(world_)
{

    createFixture(pixelsToMeters(size_.x), pixelsToMeters(size_.y));

    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getAsteroidTexture());

    m_sprite.setOrigin(0.5f * texManager->getAsteroidTexture().getSize().x, 0.5f * texManager->getAsteroidTexture().getSize().y);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;
    // Set Datas
    m_userData->setLocalId(getGlobalId());
    m_userData->setType(UserDataType::ASTEROID);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 generator(rd()); // seed the generator

    std::uniform_real_distribution<> rdnForceX(-0.1f, 0.1f); // define the range
    std::uniform_real_distribution<> rndForceY(-0.1f, 0.1f); // define the range
    std::uniform_int_distribution<> rndAngle(0, 360); // define the range
    std::uniform_int_distribution<> rndPositionX(0, pixelsToMeters(size_.x)); // define the range
    std::uniform_int_distribution<> rndPositionY(0, pixelsToMeters(size_.y)); // define the range

    b2Vec2 rdnPos(rndPositionX(generator), -1.0f * rndPositionY(generator));
    m_body->SetTransform(rdnPos, rndAngle(generator));

    b2Vec2 initialForce = b2Vec2(rdnForceX(generator), rndForceY(generator));
    m_body->ApplyLinearImpulseToCenter(initialForce, true);

    m_body->SetLinearDamping(0.0f);
    m_body->SetAngularDamping(0.0f);

}


//Asteroid::~Asteroid()
//{
//
//}


void Asteroid::createFixture(const float sizeX, const float sizeY)
{
    
    // Shape of the physical (A box)
    b2CircleShape hitBox;
    hitBox.m_radius = pixelsToMeters(sizeX * 0.5f);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 1.0f; // Make it bounce a little bit
    m_body->CreateFixture(&playerFixtureDef);

}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
	target.draw(m_sprite, states);
}

void Asteroid::setIsDead()
{
    m_isDead = true;
}
bool Asteroid::getIsDead()
{
    return m_isDead;
}

long Asteroid::getLocalId()
{
    return m_userData->getLocalId();
}

long Asteroid::getGlobalId()
{
    return m_localIdAsteroid++;
}
