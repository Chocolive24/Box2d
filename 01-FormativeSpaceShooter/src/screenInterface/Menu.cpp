#include "screenInterface/Menu.h"

#include "Game.h"
#include "core/Properties.h"

Menu::Menu(Game& game) : _game(game)
{
    sf::Vector2f windowSize(Properties::WINDOW_WIDTH, Properties::WINDOW_HEIGHT);

    _startButton.Init(windowSize.x / 2.0f, windowSize.y / 4.0f, sf::Vector2f(300, 100),
        "START", 60, "data/sprites/PNG/Keys/Space-Key.png");
    _exitButton.Init(windowSize.x / 2.0f, windowSize.y * 0.75, sf::Vector2f(300, 100),
        "EXIT", 60, "data/sprites/PNG/Keys/Esc-Key.png");

    _gameOverButton.InitShape(windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Vector2f(500, 100));
    _gameOverButton.InitText("GAME OVER", 60);

    _exitText.Init("PRESS ESCAPE TO EXIT", Properties::WINDOW_WIDTH / 2.0f, 
				   Properties::WINDOW_HEIGHT * 0.90f, 30, Properties::GREEN);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!_game.IsStarted())
    {
        target.draw(_startButton);
        target.draw(_exitButton);
    }

    if(_game.IsStarted() && !_game.IsShopOpen())
    {
        target.draw(_exitText);
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