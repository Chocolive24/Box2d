#include "screenInterface/Shop.h"

Shop::Shop(Score& score) :
	_laserUpgrade(UpgradeType::LASER, 100, "data/sprites/PNG/Lasers/laserRed01.png"),
	_bombUpgrade(UpgradeType::BOMB, 80, "data/sprites/PNG/Lasers/laserRed08.png"),
	_score(score)

{
	
}

void Shop::BuyAnUpgrade(UpgradeType upgradeType)
{
	// TODO mettre un objet Upgrade upgarde en argument et faire : upgarde.getCost, upgrade.GetLevel etc....
	// TODO dans game appeler buyanupgrade avec un getter de l'upgrade en question.
	if (upgradeType == UpgradeType::LASER)
	{
		if (_score.GetScorePoints() >= _laserUpgrade.GetCost() &&
			_laserUpgrade.GetLevel() <= _laserUpgrade.GetMaxLevel())
		{
			_score.DecreaseScore(_laserUpgrade.GetCost());
			_laserUpgrade.SetCost(_laserUpgrade.GetCost() + 3);
			_laserUpgrade.UpLevel();
			_mustBeUpdated = true;
		}
	}
}

void Shop::Update()
{
	if (_mustBeUpdated)
	{
		_score.Update();
		_laserUpgrade.SetCost(_laserUpgrade.GetCost());
		_laserUpgrade.UpdateCostText(std::to_string(_laserUpgrade.GetCost()));
		_mustBeUpdated = false;
	}
	
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_laserUpgrade, states);
	target.draw(_score);
}
