#include "screenInterface/Shop.h"

#include "core/Properties.h"

Shop::Shop(Score& score) :
	_score(score),
	_laserUpgrade(UpgradeType::LASER, 150),
	_bombUpgrade(UpgradeType::BOMB, 80),
	_hpUpgrade(UpgradeType::HP, 200)

{
	_shopTitle.InitShape(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.10,
		sf::Vector2f(300, 100));

	_shopTitle.InitText("SHOP", 60);

	_instructions.Init("You can buy upgrades with your score points", Properties::WINDOW_WIDTH / 2.0f,
		Properties::WINDOW_HEIGHT * 0.20, 30, Properties::GREEN);



	float fifthOfWindowW = Properties::WINDOW_WIDTH / 5.0f;
	float sixthOfWindowH = Properties::WINDOW_HEIGHT * 0.60;

	_laserUpgrade.InitSprite("data/sprites/PNG/Lasers/laserRed01.png");

	sf::Vector2f buttonsSize(300, 100);

	_laserUpgrade.setPosition(fifthOfWindowW, sixthOfWindowH - buttonsSize.y);
	_laserUpgrade.scale(2, 2);
	_laserUpgrade.rotate(45);

	_laserUpgrade.createPriceButton(fifthOfWindowW, sixthOfWindowH, buttonsSize,
		"data/sprites/PNG/Keys/1-Key.png");
	_laserUpgrade.createTitle("+ 1 Laser");

	_bombUpgrade.InitSprite("data/sprites/PNG/Lasers/laserRed08.png");
	_bombUpgrade.setPosition(fifthOfWindowW* 2.5f, sixthOfWindowH - buttonsSize.y);
	_bombUpgrade.scale(1.75, 1.75);

	_bombUpgrade.createPriceButton(fifthOfWindowW * 2.5f, sixthOfWindowH, buttonsSize,
		"data/sprites/PNG/Keys/2-Key.png");
	_bombUpgrade.createTitle("+ 1 Bomb");
	
	_hpUpVisual = _hpUpgrade.CreateAShape(sf::Vector2f(200, 20), fifthOfWindowW * 4.0f,
		sixthOfWindowH - buttonsSize.y, Properties::GREEN);
	_hpUpVisual.setOrigin(_hpUpVisual.getGlobalBounds().width / 2.0f, _hpUpVisual.getGlobalBounds().height / 2.0f);
	_hpUpVisual.setOutlineThickness(2.0f);
	_hpUpVisual.setOutlineColor(sf::Color::Black);

	_hpUpgrade.createPriceButton(fifthOfWindowW * 4.0f, sixthOfWindowH, buttonsSize,
		"data/sprites/PNG/Keys/3-Key.png");
	_hpUpgrade.createTitle("+ 20 HP");
}

bool Shop::BuyAnUpgrade(Upgrade& upgrade)
{
	if (_score.GetScorePoints() >= upgrade.GetCost() &&
		upgrade.GetLevel() < upgrade.GetMaxLevel())
	{
		_score.DecreaseScore(upgrade.GetCost());
		upgrade.SetCost(upgrade.GetCost() * 2);
		upgrade.UpLevel();

		return true;
	}

	return false;
}

void Shop::Update()
{
	_score.Update();

	_laserUpgrade.SetCost(_laserUpgrade.GetCost());
	_laserUpgrade.UpdateCostText(std::to_string(_laserUpgrade.GetCost()));

	_bombUpgrade.SetCost(_bombUpgrade.GetCost());
	_bombUpgrade.UpdateCostText(std::to_string(_bombUpgrade.GetCost()));

	_hpUpgrade.SetCost(_hpUpgrade.GetCost());
	_hpUpgrade.UpdateCostText(std::to_string(_hpUpgrade.GetCost()));
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shopTitle, states);
	target.draw(_instructions, states);
	target.draw(_laserUpgrade, states);
	target.draw(_bombUpgrade);
	target.draw(_hpUpgrade);
	target.draw(_hpUpVisual);
	target.draw(_score);
}
