#include "screenInterface/UIManager.h"

#include "screenInterface/Life.h"

UIManager::UIManager(WaveManager& waveManager, Player& player) :
	_player(player),
	_lifeBar(_player),
    _waveManager(waveManager)
{
	_destroyWaveUI.Init(_waveManager);
    InitLives();
}

void UIManager::InitLives()
{
    for (int width = 0; width < _player.GetMaxLives(); width++)
    {
        _lives.emplace_back(_player);

        _lives.back().SetPosition(_lifeBar.GetPosition().x + _lives.back().GetLocalBounds().width * width * 1.2f,
            _lifeBar.GetPosition().y + 2 * _lifeBar.GetLocalBounds().height);
    }
}

void UIManager::Update(sf::Time elapsed)
{
    _lifeBar.Update();
    _lives.back().Update(elapsed, _lives);
    _score.Update();

	_destroyWaveUI.Update(_waveManager);
}

void UIManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_lifeBar);

    for (auto& life : _lives)
    {
        target.draw(life);
    }

    target.draw(_score);

	target.draw(_destroyWaveUI);
}
