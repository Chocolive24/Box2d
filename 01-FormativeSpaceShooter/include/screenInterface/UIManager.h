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
	DestroyWaveUI _destroyWaveUI;

public:
	UIManager(WaveManager& waveManager, Player& player);

	void InitLives();


	void Update(sf::Time elapsed);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::list<Life>& GetLives() { return _lives; }
	Score& GetScore() { return _score; }
};
