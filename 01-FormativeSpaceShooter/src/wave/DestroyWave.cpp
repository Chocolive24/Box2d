#include "Wave/DestroyWave.h"

#include <iostream>

#include "core/Properties.h"

int DestroyWave::_numOfEntityToDestroy = 0;
int DestroyWave::_maxNumOfEntityToDestroy = 100;

DestroyWave::DestroyWave(int numOfEntity, WaveType type) : Wave(type)
{
	_numOfEntityToDestroy = numOfEntity;
}

void DestroyWave::update(sf::Time elapsed, Score& score)
{
	if (_currentEntityDestroyed >= _numOfEntityToDestroy)
	{
		_started = false;
	}
}

std::string DestroyWave::EntittyToDestroyToString(WaveType type)
{
	if (type == WaveType::DESTROY_METEOR)
	{
		return "METEOR";
	}

	else
	{
		return "NONE";
	}
}

std::string DestroyWave::StateToString()
{
	std::string string;

	string += std::to_string(_currentEntityDestroyed);

	string += " / ";

	string += std::to_string(_numOfEntityToDestroy);

	return string;
}

std::string DestroyWave::WinConditionToString(WaveType type)
{
	std::string string;

	string += "DESTROY ";

	string += EntittyToDestroyToString(type);

	return string;
}
