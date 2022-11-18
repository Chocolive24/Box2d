#include "screenInterface/LifeBar.h"

#include "Player.h"
#include "core/Properties.h"

LifeBar::LifeBar(Player& player) : _player(player)
{
    _damagedLifeBar = CreateAShape(sf::Vector2f((float)(2 * _player.GetMaxLife()), 20.0f),
								   Properties::WINDOW_WIDTH * 0.01f, 
								   Properties::WINDOW_HEIGHT * 0.02f, sf::Color::Red);

    _damagedLifeBar.setOutlineThickness(2.0f);
    _damagedLifeBar.setOutlineColor(sf::Color::Black);

    _currentLifeBar = CreateAShape(sf::Vector2f((float)(2 * _player.GetMaxLife()), 20.0f),
								    Properties::WINDOW_WIDTH * 0.01f,
								    Properties::WINDOW_HEIGHT * 0.02f, Properties::GREEN);
}

void LifeBar::Update()
{
    _damagedLifeBar.setSize(sf::Vector2f(2 * _player.GetMaxLife(), 20));
	_currentLifeBar.setSize(sf::Vector2f(2 * _player.GetCurrentLife(), 20));
}

void LifeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_damagedLifeBar, states);
    target.draw(_currentLifeBar, states);
}