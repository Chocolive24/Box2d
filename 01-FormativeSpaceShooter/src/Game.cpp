#include "Game.h"

#include <iostream>


#include "core/Utility.h"
#include "core/Properties.h"

Game::Game() :
    _gravity(0.0f, 0.0f),
    _world(_gravity),
    _player(*this),
	_uiManager(_waveManager, _player),
	_bombUIManager(_player, *this),
	_animationManager(_player),
	_shop(_uiManager.GetScore()),
    _contactListener(*this)

{
    _world.SetContactListener(&_contactListener);
}

void Game::Init()
{
    sf::Vector2f windowSize(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT);

    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "The Game");

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(120);

    CreateBackground();

    _edges.emplace_back(*this, Properties::LEFT_DOWN_CORNER, Properties::RIGHT_DOWN_CORNER);
    _edges.emplace_back(*this, Properties::LEFT_DOWN_CORNER, Properties::LEFT_UP_CORNER);
    _edges.emplace_back(*this, Properties::LEFT_UP_CORNER, Properties::RIGHT_UP_CORNER);
    _edges.emplace_back(*this, Properties::RIGHT_UP_CORNER, Properties::RIGHT_DOWN_CORNER);


    _startButton.Init(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(300, 100),
					  "START", 60,"data/sprites/PNG/Keys/Space-Key.png");
    _exitButton.Init(windowSize.x / 2.0f, windowSize.y * 0.75, sf::Vector2f(300, 100),
        "EXIT", 60, "data/sprites/PNG/Keys/Esc-Key.png");

    _gameOverButton.InitShape(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(500, 100));
    _gameOverButton.InitText("GAME OVER", 60);

    _restartButton.Init(windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Vector2f(400, 100),
        "RESTART", 60, "data/sprites/PNG/Keys/Space-Key.png");

    

    AddBombsUI();
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

void Game::AddMeteors()
{
    _meteors.emplace_back(*this);
}

void Game::AddBombsUI()
{
    _bombsUI.clear();

    for (int i = 0; i < _player.GetBombNbr(); i++)
    {
        _bombsUI.emplace_front(_player, *this);

        _bombsUI.front().SetPosition(_uiManager._lifeBar.GetPosition().x +
            _uiManager._lives.front().GetLocalBounds().width * i * 1.2f - 3.0f,
            _uiManager._lifeBar.GetPosition().y + 4.5 * _uiManager._lifeBar.GetLocalBounds().height);
    }
}

void Game::CheckInput()
{
    if (_start && !_shopOpen)
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

    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.key.code == sf::Keyboard::Escape && !_start))
        {
            _window.close();
        }

        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Space && !_shopOpen)
            {
                if (!_start)
                {
                    _start = true;
                }

                else if (_isPlayerDead)
                {
                    Restart();
                    _isPlayerDead = false;
                }

                else
                {
                    if (_player.CanShoot())
                    {
                        _player.Shoot(_shop.GetLaserUpgrade().GetLevel());
                        _soundManager.PlayLaserSound();
                    }
                }
            }

            if (event.key.code == sf::Keyboard::Key::Q && !_shopOpen && _player.GetBombNbr() > 0)
            {
                _player.ThrowBomb(_world);
                _bombsUI.front().SetToUsed();
                _soundManager.PlayBombSound();
            }

            if (_start)
            {
                if (!_shopOpen)
                {
                    if (event.key.code == sf::Keyboard::Key::Num1)
                        _shopOpen = true;
                }

                else
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
                            AddBombsUI();
                        }
                    }

                    else if (event.key.code == sf::Keyboard::Key::Num3)
                    {
                        if (_shop.BuyAnUpgrade(_shop.GetHpUpgrade()))
                        {
                            _player.SetNewLife(20);
                        }
                    }

                    else if (event.key.code == sf::Keyboard::Key::Escape && _shopOpen)
                    {
                        _shopOpen = false;
                    }
                }
            }
        }
    }
}

void Game::UpdateGame(sf::Time elapsed)
{
    if (_start && !_shopOpen && !_isPlayerDead)
    {
        _totalElapsed += elapsed;

        if (_totalElapsed.asSeconds() >= Properties::METEOR_COOLDOWN)
        {
            _meteors.emplace_back(*this);
            _meteors.back().Move();

            _totalElapsed = sf::Time::Zero;
        }

        if (!_waveManager.IsRandomWaveSetUp())
        {
            _waveManager.SetARandomWave();

            _waveManager.SetRandomWaveToSetUp();
        }

        if (_waveManager.GetTheRandomWave() == 1)
        {
            _waveManager.Update(WaveType::DESTROY_ENTITY, elapsed);

            if (_waveManager.GetDestroyWave().IsFinished())
            {
                //_shopOpen = true;
                _waveManager.GetDestroyWave().SetToUnFinished();
                _waveManager.SetRandomWaveToNotSetUp();
            }
        }

        else if (_waveManager.GetTheRandomWave() == 2)
        {
            _waveManager.Update(WaveType::SURVIVE, elapsed);

            if (_waveManager.GetSurviveWave().IsFinished())
            {
                //_shopOpen = true;
                _waveManager.GetSurviveWave().SetToUnFinished();
                _waveManager.SetRandomWaveToNotSetUp();
            }
        }

        _uiManager.Update(elapsed);

        // Updating the world with a delay
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world.Step(timeStep, velocityIterations, positionIterations);

        

        UpdateGameObjects(elapsed);

        _bombUIManager.Update(elapsed, _bombsUI);
    }

    if (_shopOpen)
    {
        _shop.Update();
        _uiManager.GetScore().SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.25f);
        _exitButton.SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.90f);
    }

    else
    {
    	_uiManager.GetScore().SetPosition(Properties::WINDOW_WIDTH * 0.885f, Properties::WINDOW_HEIGHT * 0.02f);
        _exitButton.SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.75f);
    }
    
}

void Game::UpdateGameObjects(sf::Time elapsed)
{
    for (auto& meteor : _meteors)
    {
        meteor.update(elapsed);

        /*if (meteor.IsDestroyed())
        {
            _explosions.emplace_back(*this, meteor.GetBody()->GetPosition());
            _explosions.back().update(elapsed);
            _soundManager.PlayExplosionSound();
        }*/
    }

    std::erase_if(_meteors, [](Meteor& meteor) { return meteor.IsDestroyed(); });

    _player.update(elapsed);

    if (_isPlayerCollidingMeteor)
    {
        _animationManager.CollisionWithMeteorAnim(elapsed, _isPlayerCollidingMeteor);
    }
}

void Game::Render()
{
    _window.clear(sf::Color::Black);
    
    for (auto& backgroundSprite : _background)
    {
        _window.draw(backgroundSprite);
    }

    if (!_start)
    {
        _window.draw(_startButton);
        _window.draw(_exitButton);
    }

    if (_start && !_shopOpen && !_isPlayerDead)
    {
        for (auto& meteor : _meteors)
        {
            _window.draw(meteor);
        }

		/*for (auto& explosion : _explosions)
		{
            _window.draw(explosion);
		}*/

        _window.draw(_player);

        for (auto& bomb : _bombsUI)
        {
            _window.draw(bomb);
        }

        _window.draw(_waveManager);
        _window.draw(_uiManager);
    }

    if (_shopOpen)
    {
        _window.draw(_shop);
        _window.draw(_exitButton);
    }

    if (_isPlayerDead)
    {
        _window.draw(_gameOverButton);
        _window.draw(_restartButton);
        _window.draw(_exitButton);
    }

    _window.display();
}

void Game::Restart()
{
    Init();
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
