#pragma once
#include <SFML/Graphics.hpp>

#include "BombIcon.h"
#include "LifeBar.h"
#include "Score.h"
#include "Wave/WaveManager.h"

#include "Life.h"

// UserInterface Manager
class UIManager : public sf::Drawable
{
public:
	Player& _player;

	LifeBar _lifeBar;
	std::list<Life> _lives;
	std::list<BombIcon> _bombsIcon;
	Score _score;

	WaveManager& _waveManager;

	sf::Time _titleWaveDuration;
	GameText _waveNumberText;
	GameText _winConditionText;
	GameText _waveReached;

	GameText _waveStateText;
	DrawableObject _entitiyIcon;
	bool _loaded = false;

public:
	UIManager(WaveManager& waveManager, Player& player);

	void InitLives();

	void UpdateBombsIcon();
	void UpdateWaveNumberText();
	
	void Update(sf::Time elapsed, WaveType type);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::list<Life>& GetLives() { return _lives; }
	Score& GetScore() { return _score; }
	GameText& GetWaveNumberText() { return _waveNumberText; }
};
