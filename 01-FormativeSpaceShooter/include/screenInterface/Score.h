#pragma once

#include "SFML/Graphics.hpp"

class Score : public sf::Drawable
{
private:
	sf::Font _font;
	sf::Text _scoreText;

	int _scorePoints = 1000;

public:
	Score();

	sf::Text Init(std::string string, float x, float y);

	int GetScorePoints() { return _scorePoints; }
	void IncreaseScore(int scorePoints) { _scorePoints += scorePoints; }
	void DecreaseScore(int scorePoints) { _scorePoints -= scorePoints; }
	void SetPosition(float x, float y) { _scoreText.setPosition(x, y); }

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};