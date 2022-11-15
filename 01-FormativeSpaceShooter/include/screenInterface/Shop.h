#pragma once

#include "Button.h"
#include "Score.h"
#include "Upgrade.h"
#include "SFML/Graphics.hpp"

class Shop : public sf::Drawable
{
private:
	Score& _score;

	Upgrade _laserUpgrade;
	Upgrade _bombUpgrade;
	Upgrade _hpUpgrade;
	sf::RectangleShape _hpUpVisual;

	Button _shopTitle;
	GameText _instructions;
	sf::Font _font;
	Button _laserUpButton;

public:
	Shop(Score& score);

	Upgrade& GetLaserUpgrade() { return _laserUpgrade; }
	Upgrade& GetBombUpgrade() { return _bombUpgrade; }
	Upgrade& GetHpUpgrade() { return _hpUpgrade; }

	bool BuyAnUpgrade(Upgrade& upgrade);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};