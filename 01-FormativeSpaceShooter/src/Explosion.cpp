#include "Explosion.h"

#include <box2d/b2_circle_shape.h>

#include "Game.h"

class Game;

Explosion::Explosion(Game& game, b2Vec2 meteorPosition) : _game(game)
{
    createSprite("data/sprites/PNG/Effects/explosion.png");

    createBody(_game.GetWorld(), meteorPosition);
    b2CircleShape hitBox = createCicrleHitBox();

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::EXPLOSION);

    createFixture(hitBox, (int16)_userData->GetType(), _userData);
}

void Explosion::update(sf::Time elapsed)
{
	GameObject::update(elapsed);
    b2CircleShape hitBox = createCicrleHitBox();

    if (hitBox.m_radius < 50)
    {
        hitBox.m_radius += 1;
        _sprite.scale(2, 2);
    }

    
    createFixture(hitBox, (int16)_userData->GetType(), _userData);
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
}
