#include "screenInterface/BombIcon.h"

#include <list>
#include "Game.h"

BombIcon::BombIcon()
{
    InitSprite("data/sprites/PNG/Lasers/laserRed08.png");
    scale(0.75f, 0.75f);
    _sprite.setOrigin(0, 0);
}

void BombIcon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableObject::draw(target, states);
}