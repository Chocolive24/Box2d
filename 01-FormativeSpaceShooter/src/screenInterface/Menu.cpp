#include "screenInterface/Menu.h"

#include "Game.h"
#include "core/Properties.h"

Menu::Menu(Game& game) : _game(game)
{
    sf::Vector2f windowSize(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT);

    _startButton.Init(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(300, 100),
        "START", 60, "data/sprites/PNG/Keys/1-Key.png");

    _controlsButton.Init(windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Vector2f(300, 100),
        "CONTROLS", 40, "data/sprites/PNG/Keys/2-Key.png");

    _exitButton.Init(windowSize.x / 2.0f, windowSize.y * 0.75, sf::Vector2f(300, 100),
        "EXIT", 60, "data/sprites/PNG/Keys/Esc-Key.png");

    _gameOverButton.InitShape(windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Vector2f(500, 100));
    _gameOverButton.InitText("GAME OVER", 60);

    _moveControls.Init("W / A / S / D : MOVE", windowSize.x / 2.0f, windowSize.y * 0.16f, 
					  60, Properties::GREEN);
    _laserControl.Init("LEFT CLICK : SHOOT LASER", windowSize.x / 2.0f, windowSize.y * 0.32f,
        60, Properties::GREEN);
    _bombControl.Init("RIGHT CLICK : THROW BOMB", windowSize.x / 2.0f, windowSize.y * 0.48f,
        60, Properties::GREEN);

    _mouseLooking.Init("the ship is constantly looking at the direction of the mouse",
        windowSize.x / 2.0f, windowSize.y * 0.64f,
        40, Properties::GREEN);

    _leaveControlMenu.Init("PRESS ESC TO RETURN TO THE MENU", windowSize.x / 2.0f, windowSize.y * 0.80f,
        30, sf::Color::Red);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!_game.IsStarted())
    {
        if (!_showControls)
        {
            target.draw(_startButton);
            target.draw(_controlsButton);
            target.draw(_exitButton);
        }

        else
        {
            target.draw(_moveControls);
            target.draw(_laserControl);
            target.draw(_bombControl);
            target.draw(_mouseLooking);
            target.draw(_leaveControlMenu);
        }

        
    }

    if (_game.IsShopOpen())
    {
        target.draw(_exitButton);
    }

    if (_game.GetPlayer().IsDead())
    {
        target.draw(_gameOverButton);
        target.draw(_restartButton);
        target.draw(_exitButton);
    }
}