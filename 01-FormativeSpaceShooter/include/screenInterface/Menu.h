#pragma once

#include "Button.h"
#include "SFML/Graphics.hpp"

class Game;

class Menu : public sf::Drawable
{
private:
	Game& _game;

	Button _startButton;
	Button _controlsButton;
	Button _exitButton;
	Button _gameOverButton;
	Button _restartButton;

	GameText _moveControls;
	GameText _laserControl;
	GameText _bombControl;
	GameText _mouseLooking;
	GameText _leaveControlMenu;

	bool _showControls = false;

public:
	Menu(Game& game);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Button& GetExitButton() { return _exitButton; }
	bool ShowControls() { return _showControls; }
	void SetShowControls(bool showControls) { _showControls = showControls; }
};