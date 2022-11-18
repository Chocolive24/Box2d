#pragma once

#include "GameText.h"
#include "SFML/Graphics.hpp"

class Score : public GameText
{
private:
	int _scorePoints = 0;

public:
	Score();

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	int GetScorePoints() { return _scorePoints; }
	void IncreaseScore(int scorePoints) { _scorePoints += scorePoints; }
	void DecreaseScore(int scorePoints) { _scorePoints -= scorePoints; }
	void SetPosition(float x, float y) { _text.setPosition(x, y); }
};