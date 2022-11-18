#include "soundDesign/Music.h"

Music::Music()
{
	if (!_mainTheme.openFromFile("data/sound/main_theme.wav"))
	{
		return;
	}

	_mainTheme.setLoop(true);
	_mainTheme.setVolume(25);

	if (!_gameOver.openFromFile("data/sound/game_over.wav"))
	{
		return;
	}

	if (!_titleTheme.openFromFile("data/sound/title_theme.wav"))
	{
		return;
	}
}