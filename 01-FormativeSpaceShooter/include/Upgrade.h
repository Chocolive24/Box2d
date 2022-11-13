#pragma once

#include "core/GameObject.h"
#include "screenInterface/Button.h"

enum class UpgradeType
{
	LASER,
	BOMB,
	HP,

};

class Upgrade : public GameObject
{
private:
	UpgradeType _type;

	int _cost;

	int _level = 1;
	int _maxlevel = 5;

	Button _priceButton;
	Button _titleButton;

public:
	Upgrade(UpgradeType type, int cost);

	int GetCost() { return _cost; }
	void SetCost(int newCost) { _cost = newCost; }
	int GetLevel() { return _level; }
	int GetMaxLevel() { return _maxlevel; }
	void UpLevel() { _level++; }

	void UpdateCostText(std::string newText);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};