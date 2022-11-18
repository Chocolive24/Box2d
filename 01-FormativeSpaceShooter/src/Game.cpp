#include "Game.h"

#include <iostream>
#include "core/Utility.h"
#include "core/Properties.h"

Game::Game() :
    _gravity(0.0f, 0.0f),
    _world(_gravity),
    _player(*this),
	_menuManager(*this),
	_meteorManager(*this),
	_waveManager(_player),
	_uiManager(*this, _waveManager, _player),
	_animationManager(_player),
	_shop(_uiManager.GetScore()),
    _contactListener(*this)

{
    _world.SetContactListener(&_contactListener);
}

void Game::Init()
{
    sf::Vector2f windowSize(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT);

    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "Space Shooter",
        sf::Style::Fullscreen);

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(120);

    CreateBackground();

    _edges.emplace_back(*this, Properties::LEFT_DOWN_CORNER, Properties::RIGHT_DOWN_CORNER);
    _edges.emplace_back(*this, Properties::LEFT_DOWN_CORNER, Properties::LEFT_UP_CORNER);
    _edges.emplace_back(*this, Properties::LEFT_UP_CORNER, Properties::RIGHT_UP_CORNER);
    _edges.emplace_back(*this, Properties::RIGHT_UP_CORNER, Properties::RIGHT_DOWN_CORNER);

    _musicManager.PlayTitleTheme();
}

void Game::CheckInput()
{
    CheckKeyPressed();
    CheckPollEvent();
}

void Game::UpdateGame(sf::Time& elapsed)
{
    if (_start && !_shopOpen)
    {
        _waveManager.Update(elapsed, _uiManager.GetScore());

        _shopOpen = _waveManager.IsWaveFinished();

        _uiManager.Update(elapsed, _waveManager.GetWaveType());

        _animationManager.Update(elapsed);

        _meteorManager.Update(elapsed);

        if (!_player.IsDead())
        {
            // Updating the world with a delay
            float timeStep = 1.0f / 60.0f;
            int32 velocityIterations = 6;
            int32 positionIterations = 2;
            _world.Step(timeStep, velocityIterations, positionIterations);

            UpdateGameObjects(elapsed);

            if (GetUIManager().GetLives().empty())
            {
                _player.SetToDead();
                _musicManager.StopMainTheme();
                _musicManager.PlayGameOverMusic();
            }
        }
    }

    if (_shopOpen && !_player.IsDead())
    {
        _shop.Update();
        _uiManager.GetScore().SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.25f);
        _menuManager.GetExitButton().SetPosition(Properties::WINDOW_WIDTH / 2.0f, 
												 Properties::WINDOW_HEIGHT * 0.90f);

        _meteorManager.GetMeteors().clear();
        _meteorManager.GetMeteorExplosions().clear();

        for (auto& laser : _player.GetLasers())
        {
            laser.SetToDestroyed();
        }

        for (auto& bomb : _player.GetBombs())
        {
            bomb.SetToHasExploded();
        }
    }

    else if (!_shopOpen && !_player.IsDead())
    {
        _uiManager.GetScore().SetPosition(Properties::WINDOW_WIDTH * 0.885f, Properties::WINDOW_HEIGHT * 0.02f);
        _menuManager.GetExitButton().SetPosition(Properties::WINDOW_WIDTH / 2.0f, 
												 Properties::WINDOW_HEIGHT * 0.75f);
    }
}

void Game::UpdateGameObjects(sf::Time& elapsed)
{
    _player.update(elapsed);
}

void Game::Render()
{
    _window.clear(sf::Color::Black);
    
    for (auto& backgroundSprite : _background)
    {
        _window.draw(backgroundSprite);
    }

    if (_shopOpen)
    {
        _window.draw(_shop);
    }

    if (_start && !_shopOpen)
    {
       if (!_player.IsDead())
       {
	        _window.draw(_meteorManager);
	        _window.draw(_player);
       }

        _window.draw(_uiManager);
    }

    _window.draw(_menuManager);

    _window.display();
}

void Game::CheckKeyPressed()
{
    if (_start && !_shopOpen)
    {
        if (_waveManager.GetRandomWaveNumber() != (int)SurviveWaveType::CANT_MOVE &&
            _player.CanBeControlled())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                _player.Move(b2Vec2(0.3f, 0));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                _player.Move(b2Vec2(-0.3f, 0));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                _player.Move(b2Vec2(0, 0.3f));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                _player.Move(b2Vec2(0, -0.3f));
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                _player.SetLinearDamping(1.5f);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player.CanBeControlled())
        {
            if (_player.CanShoot())
            {
                _player.Shoot(_shop.GetLaserUpgrade().GetLevel());
                _soundManager.PlayLaserSound();
            }
        }
    }
}

void Game::CheckPollEvent()
{
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.key.code == sf::Keyboard::Escape && !_shopOpen && !_menuManager.ShowControls()))
        {
            _window.close();
        }

        else if (event.type == sf::Event::KeyReleased)
        {
            if(!_start && !_shopOpen)
            {
                if (event.key.code == sf::Keyboard::Key::Num1 && !_menuManager.ShowControls())
                {
                    _start = true;
                    _musicManager.StopTitleTheme();
                    _musicManager.PlayMaintheme();
                    _waveManager.StartARandomWave();
                }

                else if (event.key.code == sf::Keyboard::Key::Num2)
                {
                	_menuManager.SetShowControls(true);
                }

                else if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    _menuManager.SetShowControls(false);
                }
                
            }

            if (_start && _shopOpen)
            {
                if (event.key.code == sf::Keyboard::Key::Num1)
                {
                    _shop.BuyAnUpgrade(_shop.GetLaserUpgrade());
                }

                else if (event.key.code == sf::Keyboard::Key::Num2)
                {
                    if (_player.GetBombNbr() <= 5 && _shop.BuyAnUpgrade(_shop.GetBombUpgrade()))
                    {
                        _player.SetBombNumber(1);
                    }
                }

                else if (event.key.code == sf::Keyboard::Key::Num3)
                {
                    if (_shop.BuyAnUpgrade(_shop.GetHpUpgrade()))
                    {
                        _player.SetNewLife(20);
                    }
                }

                else if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    _shopOpen = false;
                    _waveManager.StartARandomWave();
                }
            }
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {

            if (_start && !_shopOpen)
            {
                if (event.mouseButton.button == sf::Mouse::Left && _player.CanBeControlled())
                {
                    _player.Shoot(_shop.GetLaserUpgrade().GetLevel());
                    _soundManager.PlayLaserSound();
                }

                if (event.mouseButton.button == sf::Mouse::Right && !_shopOpen && _player.GetBombNbr() > 0 &&
                    _player.CanBeControlled() && _player.CanThrowBomb())
                {
                    _player.ThrowBomb(_world);
                    _soundManager.PlayBombSound();
                }
            }
        }
    }
}

int Game::GameLoop()
{
    while (_window.isOpen())
    {
        _elapsed = _clock.restart();

        CheckInput();

        UpdateGame(_elapsed);

        Render();
    }

    return EXIT_SUCCESS;
}

void Game::CreateBackground()
{
    if (!_backgroundTexture.loadFromFile("data/sprites/Backgrounds/blue.png"))
    {
        return; // error 
    }

    _backgroundSprite.setTexture(_backgroundTexture);
    float factorX = _window.getSize().x / _backgroundSprite.getGlobalBounds().width;
    float factorY = _window.getSize().y / _backgroundSprite.getGlobalBounds().height;

    for (int width = 0; width < factorX; width++)
    {
        for (int height = 0; height < factorY; height++)
        {
            sf::Sprite sprite;
            sprite.setTexture(_backgroundTexture);
            sprite.setPosition(sprite.getLocalBounds().width * width,
                sprite.getLocalBounds().height * height);
            _background.emplace_back(sprite);
        }
    }
}
