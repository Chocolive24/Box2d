#include "Game.h"

#include <iostream>

Game::Game() :
	_gravity(0.0f, 0.0f),
	_world(_gravity)
{
}


void Game::Init()
{
    _window.create(sf::VideoMode(1200, 800), "The Game");

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(120);

    _player.Init(_world);

}

int Game::GameLoop()
{
    while (_window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.Move(b2Vec2(50, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.Move(b2Vec2(-50, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.Move(b2Vec2(0, 50));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.Move(b2Vec2(0, -50));
        }

        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;

        while (_window.pollEvent(event))
        {
            switch (event.type)
            {

                // évènement "fermeture demandée" : on ferme la fenêtre
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

        // Updating the world with a delay
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world.Step(timeStep, velocityIterations, positionIterations);


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

        // Graphical Region
        _window.clear(sf::Color::Black);

        _player.Update();

        //window.draw(something to draw);
        _window.draw(_player);

        // Window Display
        _window.display();


    }

    return EXIT_SUCCESS;
}
