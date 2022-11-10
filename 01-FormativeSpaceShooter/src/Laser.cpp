#include "Laser.h"

#include "Game.h"
#include "Properties.h"
#include "Utility.h"

Laser::Laser(Game& game, b2Vec2 playerPos) : _game(game)
{
    createSprite("data/sprites/PNG/Lasers/laserRed01.png");

    if (!_buffer.loadFromFile("data/sound/sfx_laser2.wav"))
    {
        return;
    }

    _sound.setBuffer(_buffer);

    createBody(_game.GetWorld(), playerPos);
    _hitBox = createPolygonHitBox();
    _userData = new UserData(*this);
    _userData->SetType(UserDataType::LASER);

    createFixture(_hitBox, (int)_userData->GetType(), _userData);
}

Laser::~Laser()
{
    _game.GetWorld().DestroyBody(_body);
}

void Laser::Init(b2World& world, b2Vec2 playerPos)
{
    
}

void Laser::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter(force, true);
}

void Laser::update(sf::Time elapsed)
{
    GameObject::update(elapsed);
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GameObject::draw(target, states);
}
