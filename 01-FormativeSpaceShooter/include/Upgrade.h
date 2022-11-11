#pragma once

#include "core/GameObject.h"

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

public:
	Upgrade(UpgradeType type, int cost);
};