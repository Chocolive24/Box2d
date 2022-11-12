#pragma once

#include "SFML/Graphics.hpp"

class Score : public sf::Drawable
{
private:
	sf::Font _font;
	sf::Text _scoreText;
	sf::Text _scorePointsText;

	int _scorePoints = 0;

public:
	Score();

	sf::Text Init(std::string string, float x, float y);

	int GetScorePoints() { return _scorePoints; }
	void IncreaseScore(int scorePoints) { _scorePoints += scorePoints; }
	void DecreaseScore(int scorePoints) { _scorePoints -= scorePoints; }

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};