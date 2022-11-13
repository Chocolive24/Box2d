#include "Upgrade.h"

#include "Player.h"
#include "core/Properties.h"

Upgrade::Upgrade(UpgradeType type, int cost) :
	_type(type),
	_cost(cost)

{
	

	float fifthOfWindowW = Properties::WINDOW_WIDTH / 5.0f;
	float sixthOfWindowH = Properties::WINDOW_HEIGHT * 0.60;

	if (_type == UpgradeType::LASER)
	{
		createSprite("data/sprites/PNG/Lasers/laserRed01.png");

		sf::Vector2f buttonsSize(300, 100);
		_priceButton.Init(fifthOfWindowW, sixthOfWindowH, buttonsSize, std::to_string(_cost),
			"data/sprites/PNG/Keys/Q-Key.png");

		_sprite.setPosition(fifthOfWindowW, sixthOfWindowH - buttonsSize.y);
		_sprite.scale(2, 2);
		_sprite.rotate(45);
	}

	
	//"data/sprites/PNG/Lasers/laserRed08.png"
	
}

void Upgrade::UpdateCostText(std::string newText)
{
	_priceButton.SetText(newText);
}

void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
	target.draw(_titleButton, states);
	target.draw(_priceButton, states);
}
