#include "screenInterface/Life.h"

#include "Game.h"
#include "Player.h"

Life::Life(Player& player, Game& game) : _player(player), _game(game)
{
    InitSprite("data/sprites/PNG/UI/playerLife1_red.png");
    _sprite.setOrigin(0,0);
}

void Life::Update(sf::Time elapsed, std::list<Life>& lives)
{
    if (_player.GetCurrentLife() <= 0)
    {
        _duration += elapsed;

        if (_duration.asSeconds() >= 2)
        {
            if (!_game.IsPlayerDead())
            {
                lives.back().SetToLost();
                _player.SetCurrentLifeToMax();
                _duration = sf::Time::Zero;
            }
        }
    }

    std::erase_if(lives, [](Life& life) { return life.IsLost(); });
}

void Life::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableObject::draw(target, states);
}
