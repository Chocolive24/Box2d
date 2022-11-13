#include "screenInterface/Shop.h"

#include "core/Properties.h"

Shop::Shop(Score& score) :
	_score(score),
	_laserUpgrade(UpgradeType::LASER, 100),
	_bombUpgrade(UpgradeType::BOMB, 80)

{
	_shopTitle.InitShape(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.10,
		sf::Vector2f(300, 100));

	_shopTitle.InitText("SHOP");

	if (!_font.loadFromFile("data/font/kenvector_future.ttf"))
	{
		return;
	}

	_instructions.setFont(_font);

	_instructions.setString("You can buy upgrades with your score points");
	_instructions.setCharacterSize(30);
	_instructions.setFillColor(Properties::GREEN);
	_instructions.setStyle(sf::Text::Bold);

	_instructions.setOrigin(_instructions.getLocalBounds().width / 2.0f, _instructions.getLocalBounds().height / 2.0f);
	_instructions.setPosition(Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT * 0.25);
}

void Shop::BuyAnUpgrade(Upgrade& upgrade)
{

	if (_score.GetScorePoints() >= upgrade.GetCost() &&
		upgrade.GetLevel() <= upgrade.GetMaxLevel())
	{
		_score.DecreaseScore(upgrade.GetCost());
		upgrade.SetCost(upgrade.GetCost() + 3);
		upgrade.UpLevel();
	}
	
}

void Shop::Update()
{
	_score.Update();
	_laserUpgrade.SetCost(_laserUpgrade.GetCost());
	_laserUpgrade.UpdateCostText(std::to_string(_laserUpgrade.GetCost()));
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shopTitle, states);
	target.draw(_instructions, states);
	target.draw(_laserUpgrade, states);
	target.draw(_score);
}
