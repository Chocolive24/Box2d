#include "Explosion.h"

#include <iostream>
#include <box2d/b2_circle_shape.h>

#include "Game.h"
#include "core/Utility.h"

class Game;

Explosion::Explosion(Game& game) : _game(game)
{
}

Explosion::~Explosion()
{
    _game.GetWorld().DestroyBody(_body);
}


void Explosion::Init(Game& game, b2Vec2 meteorPosition)
{
    createSprite("data/sprites/PNG/Effects/star3.png");

    createBody(_game.GetWorld(), meteorPosition, b2_kinematicBody);

    sf::Vector2f position(Utility::MetersToPixels(meteorPosition));

    _areaOfEffect.setPosition(position.x, position.y);
    _areaOfEffect.setRadius(10.0f);
    _areaOfEffect.setOrigin(_areaOfEffect.getLocalBounds().width / 2.0f,
							_areaOfEffect.getLocalBounds().height / 2.0f);
    _areaOfEffect.setFillColor(sf::Color(150, 0, 0, 100));

    b2CircleShape hitBox;
    hitBox.m_radius = Utility::PixelToMeters(_areaOfEffect.getRadius());

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::EXPLOSION);

    createFixture(hitBox, 20.0f, 0.5f,
        (uint16)UserDataType::EXPLOSION,
        (uint16)UserDataType::METEOR,
        _userData, true);
}

void Explosion::update(sf::Time elapsed)
{
	GameObject::update(elapsed);

    if (_isAnExplosion)
    {
        /*_isExplosionFinished = false;*/
        _duration += elapsed;

        if (_duration.asSeconds() <= 2.0f)
        {
            _areaOfEffect.setRadius(_areaOfEffect.getRadius() + 2);
            _areaOfEffect.setOrigin(_areaOfEffect.getGlobalBounds().width / 2.0f,
									_areaOfEffect.getGlobalBounds().height / 2.0f);

            _shape->m_radius = Utility::PixelToMeters(_areaOfEffect.getRadius());

            std::cout << "radius = " << _shape->m_radius << std::endl;

        }

        else
        {
            _isAnExplosion = false;
            _game.GetWorld().DestroyBody(_body);
            //_isExplosionFinished = true;
            _duration = sf::Time::Zero;
        }
    }
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_isAnExplosion)
    {
        GameObject::draw(target, states);
        target.draw(_areaOfEffect);
    }
}
