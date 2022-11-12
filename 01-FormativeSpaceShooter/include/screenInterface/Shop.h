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

	Button _laserUpButton;

public:
	Shop(Score& score);

	void BuyAnUpgrade(UpgradeType upgradeType);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};