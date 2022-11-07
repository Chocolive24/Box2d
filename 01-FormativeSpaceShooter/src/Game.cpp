#include "Game.h"

#include <iostream>

#include "Properties.h"
#include "Utility.h"

Game::Game() :
	_gravity(0.0f, 0.0f),
	_world(_gravity)
{
}

void Game::Init()
{
    sf::Vector2f windowSize(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT);

    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "The Game");

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(120);

    _startButton.Init(windowSize.x / 2.0f, windowSize.y / 4.0f, 
					  "START", "data/sprites/PNG/Keys/Space-Key.png");
    _exitButton.Init(windowSize.x / 2.0f, windowSize.y / 1.5f,
        "EXIT", "data/sprites/PNG/Keys/Esc-Key.png");

    _player.Init(_world);

    AddMeteors();

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
    for (int i = 0; i <5; i++)
    {
        Meteor* meteor = new Meteor;

        meteor->Init(_world);

        _meteors.emplace_back(meteor);
    }
}

void Game::CheckInput()
{
    if (_start)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.Move(b2Vec2(30, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.Move(b2Vec2(-30, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.Move(b2Vec2(0, 30));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.Move(b2Vec2(0, -30));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            _player.Rotate(100.0f);
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.SetLinearDamping(1.5f);
            _player.Move(b2Vec2(0, 0));
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

        else if  (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Space)
            {
                if (!_start)
                {
                    _start = true;
                }

                else
                {
                    _player.Shoot(_world);
                }
            }
        }
        

            //case sf::Event::MouseButtonReleased:

            //    // Put in mouse position
            //    body->SetTransform(b2Vec2(event.mouseButton.x / _pixelMetersRatio,
            //        -1.0f * event.mouseButton.y / _pixelMetersRatio), body->GetAngle());
            //    //// Reset the velocity (Speed)
            //    body->SetLinearVelocity(b2Vec2_zero);


            //    //box.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            //    break;

    }
}

void Game::Update()
{
    CheckInput();

    if (_start)
    {
        // Updating the world with a delay
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world.Step(timeStep, velocityIterations, positionIterations);

        _player.Update();

        for (auto& meteor : _meteors)
        {
            meteor->Update();
        }

        for (auto& laser : _player.GetLasers())
        {
            laser->Update();
        }
    }

    
}

void Game::Draw()
{
    // Graphical Region
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

    else
    {
        for (auto& meteor : _meteors)
        {
            _window.draw(*meteor);
        }

        for (auto& laser : _player.GetLasers())
        {
            _window.draw(*laser);
        }

        _window.draw(_player);
    }
}

int Game::GameLoop()
{
    while (_window.isOpen())
    {
        /*std::cout << "body position [" << body->GetPosition().x << ":" << body->GetPosition().y
            << "]|shape position [" << box.getPosition().x << ":" << box.getPosition().y << "]" << std::endl;*/

        /*
        if (body->GetPosition().y < -(window.getSize().y / pixelMetersRatio))
        {
            std::cout << "LETSGO  LA PHYSIQUE" << std::endl;
        }

        if (box.getPosition().y > window.getSize().y)
        {
            std::cout << "LETSGO  LES GRAPH" << std::endl;
        }*/

        Update();

        Draw();

        // Window Display
        _window.display();

    }

    return EXIT_SUCCESS;
}
