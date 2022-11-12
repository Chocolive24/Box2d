#include "Upgrade.h"

Upgrade::Upgrade(UpgradeType type, int cost, std::string path) :
	_type(type),
	_cost(cost)

{
	createSprite(path);

	if (_type == UpgradeType::LASER)
	{
		_sprite.setPosition(750.0f, 350.0f);
		_sprite.scale(2, 2);
		_sprite.rotate(45);
	}

	_button.Init(750.0f, 450.0f, std::to_string(_cost),
				 "data/sprites/PNG/Keys/Q-Key.png");
}

void Upgrade::UpdateCostText(std::string newText)
{
	_button.SetText(newText);
}

void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
	target.draw(_button, states);
}
