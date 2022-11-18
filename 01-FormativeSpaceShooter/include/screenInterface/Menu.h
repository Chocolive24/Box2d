#pragma once

#include "Button.h"
#include "SFML/Graphics.hpp"

class Game;

class Menu : public sf::Drawable
{
private:
	Game& _game;

	Button _startButton;
	Button _exitButton;
	Button _gameOverButton;
	Button _restartButton;

	GameText _exitText;

public:
	Menu(Game& game);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Button& GetExitButton() { return _exitButton; }
};