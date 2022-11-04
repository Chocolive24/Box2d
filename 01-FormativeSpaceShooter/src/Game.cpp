#include "Game.h"

#include <iostream>

#include "Properties.h"

Game::Game() :
	_gravity(0.0f, 0.0f),
	_world(_gravity)
{
}

void Game::Init()
{
    _window.create(sf::VideoMode(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT), "The Game");

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(120);

    _player.Init(_world);

    if (!_backgroundTexture.loadFromFile("data/sprites/Backgrounds/purple.png"))
    {
        return; // error 
    }

    _background.setTexture(_backgroundTexture);
    float factorX = _window.getSize().x / _background.getGlobalBounds().width;
    float factorY = _window.getSize().y / _background.getGlobalBounds().height;
    _background.setScale(factorX, factorY);

}

void Game::CheckInput()
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

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _player.SetLinearDamping(1.5f);
        _player.Move(b2Vec2(0, 0));
    }

    sf::Event event;

    while (_window.pollEvent(event))
    {
        switch (event.type)
        {

        case sf::Event::Closed:
            _window.close();
            break;

            //case sf::Event::MouseButtonReleased:

            //    // Put in mouse position
            //    body->SetTransform(b2Vec2(event.mouseButton.x / _pixelMetersRatio,
            //        -1.0f * event.mouseButton.y / _pixelMetersRatio), body->GetAngle());
            //    //// Reset the velocity (Speed)
            //    body->SetLinearVelocity(b2Vec2_zero);


            //    //box.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            //    break;


        default:
            break;
        }

    }
}

void Game::Update()
{
    CheckInput();

    // Updating the world with a delay
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    _world.Step(timeStep, velocityIterations, positionIterations);

    _player.Update();
}

void Game::Draw()
{
    // Graphical Region
    _window.clear(sf::Color::Black);

    _window.draw(_background);

    _window.draw(_player);
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
