#include "screenInterface/BombUI.h"

#include <list>
#include "Game.h"

BombUI::BombUI(Player& player, Game& game) : _player(player), _game(game)
{
    InitSprite("data/sprites/PNG/Lasers/laserRed08.png");
    _sprite.setOrigin(0, 0);
    _sprite.scale(0.8, 0.8);
}

void BombUI::Update(sf::Time elapsed, std::list<BombUI>& bombsUI)
{
    std::erase_if(bombsUI, [](BombUI& bomb) { return bomb.WasUsed(); });
}

void BombUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableObject::draw(target, states);
}