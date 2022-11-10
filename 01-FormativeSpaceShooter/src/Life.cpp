#include "Life.h"

#include "Player.h"

Life::Life(Player& player) : _player(player)
{
    if (!_texture.loadFromFile("data/sprites/PNG/UI/playerLife1_red.png"))
    {
        return;
    }

    _texture.setSmooth(true);

    _sprite.setTexture(_texture);
}

void Life::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
