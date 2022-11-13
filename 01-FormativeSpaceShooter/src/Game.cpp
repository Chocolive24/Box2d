#include "Game.h"

#include <iostream>


#include "core/Utility.h"
#include "core/Properties.h"

Game::Game() :
    _gravity(0.0f, 0.0f),
    _world(_gravity),
    _contactListener(*this),
    _player(*this),
    _lifeBar(_player),
	_shop(_score)

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

    _startButton.Init(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(300, 100),
					  "START", "data/sprites/PNG/Keys/Space-Key.png");
    _exitButton.Init(windowSize.x / 2.0f, windowSize.y * 0.75, sf::Vector2f(300, 100),
        "EXIT", "data/sprites/PNG/Keys/Esc-Key.png");

    _gameOverButton.InitShape(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(500, 100));
    _gameOverButton.InitText("GAME OVER");

    _restartButton.Init(windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Vector2f(400, 100),
        "RESTART", "data/sprites/PNG/Keys/Space-Key.png");

    for (int width = 0; width < _player.GetMaxLives(); width++)
    {
        _lives.emplace_back(_player);

        _lives.back().SetPosition(_lifeBar.GetPosition().x + _lives.back().GetLocalBounds().width * width * 1.2f,
            _lifeBar.GetPosition().y + 2 * _lifeBar.GetLocalBounds().height);
    }

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

void Game::UpdateLives()
{
    if (_player.GetCurrentLife() <= 0 && !_isPlayerDead)
    {
        if(_isDieAnimationFinished)
        {
            _lives.back().SetToLost();
            _player.SetCurrentLifeToMax();
        }
    }

    std::erase_if(_lives, [](Life& life) { return life.IsLost(); });

    if (_lives.empty())
    {
        _isPlayerDead = true;
    }

}

void Game::CheckInput()
{
    if (_start && !_shopOpen)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.Move(b2Vec2(0.3f, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.Move(b2Vec2(-0.3f, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.Move(b2Vec2(0, 0.3f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.Move(b2Vec2(0, -0.3f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            _player.Rotate(-3.0f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            _player.Rotate(3.0f);
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
            if (event.key.code == sf::Keyboard::Key::Space)
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
                        _player.Shoot(_shop.GetLaserUpgrade());
                        _soundManager.PlayLaserSound();
                    }
                }
            }

            if (event.key.code == sf::Keyboard::Key::Q && !_shopOpen)
            {
                _player.ThrowBomb(_world);
                _soundManager.PlayBombSound();
            }

            if (!_shopOpen)
            {
                if (event.key.code == sf::Keyboard::Key::Num1)
                    _shopOpen = true;
            }

            else 
            {
                if (event.key.code == sf::Keyboard::Key::Q && _shopOpen)
                {
                    _shop.BuyAnUpgrade(_shop.GetLaserUpgrade());
                }
                else if (event.key.code == sf::Keyboard::Key::Escape && _shopOpen)
                {
                    _shopOpen = false;
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

        // Updating the world with a delay
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world.Step(timeStep, velocityIterations, positionIterations);

        _score.Update();

        UpdateGameObjects(elapsed);

        _lifeBar.Update();

        if (_lives.empty())
        {
            SetPlayerToDead();
        }
    }

    if (_player.GetCurrentLife() <= 0)
    {
        _isDieAnimationFinished = false;

        _dieAnimationTime += elapsed;

        if (_dieAnimationTime.asSeconds() >= 2)
        {
            _isDieAnimationFinished = true;
            _dieAnimationTime = sf::Time::Zero;
        }
    }

    UpdateLives();

    std::cout << _dieAnimationTime.asSeconds() << std::endl;

    if (_shopOpen)
    {
        _score.SetPosition(Properties::WINDOW_WIDTH / 2.0f, 300);
        _shop.Update();
        _exitButton.SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.90f);
    }

    else
    {
        _score.SetPosition(Properties::WINDOW_WIDTH * 0.885f, Properties::WINDOW_HEIGHT * 0.02f);
        _exitButton.SetPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.75);
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
        
        _window.draw(_lifeBar);

        for (auto& life : _lives)
        {
            _window.draw(life);
        }

        _window.draw(_score);
    }

    if (_shopOpen)
    {
        /*for (auto& backgroundSprite : _background)
        {
            _window.draw(backgroundSprite);
        }*/
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
        sf::Time elapsed = _clock.restart();

        CheckInput();

        UpdateGame(elapsed);

        Render();
    }

    return EXIT_SUCCESS;
}
