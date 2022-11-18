#include "screenInterface/UIManager.h"

#include <iostream>

#include "Game.h"
#include "core/Properties.h"
#include "screenInterface/Life.h"

UIManager::UIManager(Game& game, WaveManager& waveManager, Player& player) :
    _game(game),
	_player(player),
	_lifeBar(_player),
    _waveManager(waveManager)
{
    InitLives();

    _waveNumberText.Init("Wave number " + std::to_string(_waveManager.GetWaveNumber()),
				         Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 3.0f,
				         60, sf::Color::Red);

    _winConditionText.Init("not started", 
					        Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 2.5f,
					        40, sf::Color::Red);

    _waveStateText.Init("not started",
				        Properties::WINDOW_WIDTH / 2.0f,
				        Properties::WINDOW_HEIGHT * 0.036f, 50, Properties::GREEN);

    _exitText.Init("PRESS ESCAPE TO EXIT", Properties::WINDOW_WIDTH / 2.0f,
        Properties::WINDOW_HEIGHT * 0.95f, 30, Properties::GREEN);
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

void UIManager::Update(sf::Time& elapsed, WaveType type)
{
    if (!_player.IsDead())
    {

        _lifeBar.Update();

        if (!_lives.empty())
        {
            _lives.back().Update(elapsed, _lives);
        }

        UpdateBombsIcon();

        UpdateWaveNumberText();

        _winConditionText.SetString(_waveManager.GetWinConditionToString(type));
        _winConditionText.SetOriginToMiddle();

        _titleWaveDuration = sf::Time::Zero;

        _waveStateText.SetString(_waveManager.GetWaveStateToString());
        _waveStateText.SetOriginToMiddle();

        if (!_loaded)
        {
            if (_waveManager.GetRandomWaveNumber() == (int)WaveType::DESTROY_METEOR)
            {
                _entitiyIcon.InitSprite("data/sprites/PNG/Meteors/meteorBrown_big1.png");
                _entitiyIcon.scale(0.5f, 0.5);
                _loaded = true;
            }
        }

        if (_waveManager.IsWaveFinished() && _waveManager.GetRandomWaveNumber() == (int)EntityToDestroyType::METEOR)
        {
            _loaded = false;

            // Reset the scale to the original size otherwise when the icon is redrawn
            // its scale will be reduced a second time by two.
            _entitiyIcon.scale(2, 2);
        }

        _entitiyIcon.setPosition(Properties::WINDOW_WIDTH / 2.0f +
            _waveStateText.GetLocalBounds().width,
            Properties::WINDOW_HEIGHT * 0.038f);
    }

    else
    {
	    _waveReached.Init("YOU REACHED WAVE " + std::to_string(_waveManager.GetWaveNumber()),
            Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 5.0f,
            40, sf::Color::Red);

        _score.SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 4.0f);
    }

    _score.Update();
}

void UIManager::UpdateWaveNumberText()
{
    _waveNumberText.SetString("Wave number " + std::to_string(_waveManager.GetWaveNumber()));
    _waveNumberText.SetOriginToMiddle();
}

void UIManager::UpdateBombsIcon()
{
    _bombsIcon.clear();

    for (int i = 0; i < _player.GetBombNbr(); i++)
    {
        _bombsIcon.emplace_front();

        _bombsIcon.front().SetPosition(_lifeBar.GetPosition().x +
            _bombsIcon.front().GetGlobalBounds().width * i * 1.2f - 2.5f,
            _lifeBar.GetPosition().y + 5 * _lifeBar.GetLocalBounds().height);
    }
}

void UIManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!_player.IsDead())
    {
        target.draw(_lifeBar);

        for (auto& life : _lives)
        {
            target.draw(life);
        }

        for (auto& bombIcon : _bombsIcon)
        {
            target.draw(bombIcon);
        }

        target.draw(_score);

        if (!_waveManager.IsTitleTimeDone())
        {
            target.draw(_waveNumberText);
            target.draw(_winConditionText);
        }

        target.draw(_waveStateText);

        if (_waveManager.GetRandomWaveNumber() == (int)WaveType::DESTROY_METEOR)
        {
            target.draw(_entitiyIcon);
        }
    }

    else 
    {
        target.draw(_waveReached);
        target.draw(_score);
    }

    if (_game.IsStarted() && !_game.IsShopOpen() && !_player.IsDead())
    {
        target.draw(_exitText);
    }
}
