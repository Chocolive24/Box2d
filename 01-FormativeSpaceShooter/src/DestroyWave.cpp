#include "DestroyWave.h"

#include <iostream>

#include "core/Properties.h"

DestroyWave::DestroyWave() : Wave(WaveType::DESTROY_ENTITY)
{
	_numOfEntityToDestroy = 5;
}

std::string DestroyWave::EntittyToDestroyToString(EntityToDestroyType type)
{
	switch(type)
	{
	case EntityToDestroyType::METEOR:
		return "METEORS";

	case EntityToDestroyType::NONE:
		return "UNKNOWN";
	}
}

void DestroyWave::Update()
{
	if (!_started)
	{
		_numOfEntityToDestroy += 5;
		_started = true;
	}

	if (_currentEntityDestroyed >= _numOfEntityToDestroy)
	{
		_isFinished = true;
		_currentEntityDestroyed = 0;
	}

	if (_isFinished)
	{
		_started = false;
	}
}