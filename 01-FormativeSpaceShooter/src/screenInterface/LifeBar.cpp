
#include "screenInterface/LifeBar.h"

#include "Player.h"
#include "core/Properties.h"

LifeBar::LifeBar(Player& player) : _player(player)
{
    _damagedLifeBar.setSize(sf::Vector2f(2 * _player.GetMaxLife(), 20));
    _damagedLifeBar.setPosition((float)Properties::WINDOW_WIDTH * 0.01f, (float)Properties::WINDOW_HEIGHT * 0.02f);

    _damagedLifeBar.setFillColor(sf::Color::Red);
    _damagedLifeBar.setOutlineThickness(2.0f);
    _damagedLifeBar.setOutlineColor(sf::Color::Black);

    _currentLifeBar.setSize(sf::Vector2f(2 * _player.GetCurrentLife(), 20));
    _currentLifeBar.setPosition((float)Properties::WINDOW_WIDTH * 0.01f, (float)Properties::WINDOW_HEIGHT * 0.02f);

    _currentLifeBar.setFillColor(Properties::GREEN);
}

void LifeBar::Update()
{
	_currentLifeBar.setSize(sf::Vector2f(2 * _player.GetCurrentLife(), 20));
}

void LifeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_damagedLifeBar, states);
    target.draw(_currentLifeBar, states);
}