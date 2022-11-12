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

	bool _mustBeUpdated = false;

public:
	Shop(Score& score);

	Upgrade& GetLaserUpgrade() { return _laserUpgrade; }

	void BuyAnUpgrade(UpgradeType upgradeType);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};