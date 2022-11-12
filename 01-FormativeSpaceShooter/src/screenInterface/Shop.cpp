#include "screenInterface/Shop.h"

Shop::Shop(Score& score) :
	_laserUpgrade(UpgradeType::LASER, 100, "data/sprites/PNG/Lasers/laserRed01.png"),
	_bombUpgrade(UpgradeType::BOMB, 80, "data/sprites/PNG/Lasers/laserRed08.png"),
	_score(score)

{
	
}

void Shop::BuyAnUpgrade(UpgradeType upgradeType)
{
	if (upgradeType == UpgradeType::LASER)
	{
		_laserUpgrade.SetCost(_laserUpgrade.GetCost() * 3);
		_laserUpgrade.UpLevel();
	}
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_laserUpgrade, states);
}
