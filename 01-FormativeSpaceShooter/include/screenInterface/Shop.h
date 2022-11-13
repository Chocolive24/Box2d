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

	Button _shopTitle;
	sf::Text _instructions;
	sf::Font _font;
	Button _laserUpButton;

	bool _mustBeUpdated = false;

public:
	Shop(Score& score);

	Upgrade& GetLaserUpgrade() { return _laserUpgrade; }

	void BuyAnUpgrade(Upgrade& upgrade);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};