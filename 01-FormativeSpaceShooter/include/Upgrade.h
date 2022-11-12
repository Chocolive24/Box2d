#pragma once

#include "core/GameObject.h"
#include "screenInterface/Button.h"

enum class UpgradeType
{
	LASER,
	BOMB,

};

class Upgrade : public GameObject
{
private:
	UpgradeType _type;

	int _cost;

	int _level = 1;
	int _maxlevel = 5;

	Button _button;

public:
	Upgrade(UpgradeType type, int cost, std::string path);

	int GetCost() { return _cost; }
	void SetCost(int newCost) { _cost = newCost; }
	void UpLevel() { _level++; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};