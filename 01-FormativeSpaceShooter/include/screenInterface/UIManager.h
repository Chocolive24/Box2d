#pragma once
#include <SFML/Graphics.hpp>

#include "BombUI.h"
#include "DestroyWaveUI.h"
#include "LifeBar.h"
#include "Score.h"

class Life;

// UserInterface Manager
class UIManager : public sf::Drawable
{
public:
	Player& _player;

	LifeBar _lifeBar;
	std::list<Life> _lives;
	Score _score;

	WaveManager& _waveManager;

	sf::Time _titleWaveDuration;

	GameText _waveNumberText;
	GameText _winConditionText;

	GameText _waveStateText;
	DrawableObject _entitiyIcon;
	bool _loaded = false;

	

public:
	UIManager(WaveManager& waveManager, Player& player);

	void InitLives();

	void UpdateWaveNumberText();
	
	void Update(sf::Time elapsed, WaveType type);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::list<Life>& GetLives() { return _lives; }
	Score& GetScore() { return _score; }
	GameText& GetWaveNumberText() { return _waveNumberText; }
};
