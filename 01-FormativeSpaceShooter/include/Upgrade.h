#pragma once

#include "core/GameObject.h"
#include "screenInterface/Button.h"

enum class UpgradeType
{
	LASER,
	BOMB,
	HP,
};

class Upgrade : public DrawableObject
{
private:
	UpgradeType _type;

	int _cost;

	int _level = 1;
	int _maxlevel = 5;

	Button _priceButton;
	GameText _title;

public:
	Upgrade(UpgradeType type, int cost);

	int GetCost() { return _cost; }
	void SetCost(int newCost) { _cost = newCost; }
	int GetLevel() { return _level; }
	int GetMaxLevel() { return _maxlevel; }
	void UpLevel() { _level++; }

	void createPriceButton(float x, float y, sf::Vector2f size, std::string path);
	void createTitle(std::string title);

	void UpdateCostText(std::string newText);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};