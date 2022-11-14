#include "Upgrade.h"

#include "Player.h"
#include "core/Properties.h"

Upgrade::Upgrade(UpgradeType type, int cost) :
	_type(type),
	_cost(cost)

{
}

void Upgrade::createPriceButton(float x, float y, sf::Vector2f size, std::string path)
{
	_priceButton.Init(x, y, size, std::to_string(_cost),
		60, path);
}

void Upgrade::createTitle(std::string title)
{
	_title.Init(title, _priceButton.GetPosition().x,
		_priceButton.GetPosition().y * 0.65f, 30, Properties::GREEN);
}

void Upgrade::UpdateCostText(std::string newText)
{
	_priceButton.SetText(newText);
	_priceButton.SetTextOriginToMiddle();
}

void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	DrawableObject::draw(target, states);
	target.draw(_title, states);
	target.draw(_priceButton, states);
}
