#include "MeteorManager.h"

#include "Game.h"
#include "core/Properties.h"
#include "core/Utility.h"

MetorManager::MetorManager(Game& game) : _game(game)
{
}

void MetorManager::Update(sf::Time& elapsed)
{
    _totalElapsed += elapsed;

    if (_game.GetWaveManager().GetWaveNumber() % 3 == 0 && _mustIncreaseMeteorNum)
    {
        _numberOfMeteorPerSecond += 1;
        _mustIncreaseMeteorNum = false;
    }

    else if (_game.GetWaveManager().GetWaveNumber() % 3 != 0)
    {
        _mustIncreaseMeteorNum = true;
    }

    if (_totalElapsed.asSeconds() >= Properties::METEOR_COOLDOWN && _game.GetWaveManager().IsTitleTimeDone())
    {
        for (int i = 0; i < _numberOfMeteorPerSecond; i++)
        {
            _meteors.emplace_back(_game);
            _meteors.back().Move();
        }

        _totalElapsed = sf::Time::Zero;
    }

    for (auto& meteor : _meteors)
    {
        meteor.update(elapsed);

        if (meteor.IsDestroyed() && meteor.CanExplose())
        {
            _explosions.emplace_back(Utility::MetersToPixels(meteor.GetBody()->GetPosition()));
        }

        if (!_explosions.empty())
        {
            for (auto& explosion : _explosions)
            {
                explosion.Update(elapsed);
            }
        }
    }

    std::erase_if(_meteors, [](Meteor& meteor) { return meteor.IsDestroyed(); });
}

void MetorManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& meteor : _meteors)
    {
        target.draw(meteor);
    }

    
    for (auto& explosion : _explosions)
    {
        target.draw(explosion);
    }
}