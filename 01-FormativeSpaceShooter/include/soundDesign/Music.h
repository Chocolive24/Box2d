#pragma once

#include "SFML/Audio.hpp"

class Music
{
private:
	sf::Music _mainTheme;

	sf::Music _gameOver;

public:
	Music();

	void PlayMaintheme() { _mainTheme.play(); }
	void StopMainTheme() { _mainTheme.stop(); }
	void PlayGameOverMusic() { _gameOver.play(); }
	void StopGameOverMusic() { _gameOver.stop(); }
};