#pragma once
#include "Wave.h"
#include "core/GameObject.h"

enum class EntityToDestroyType
{
	METEOR,
	NONE,
};

class DestroyWave : public Wave
{
private:
	int _numOfEntityToDestroy;
	int _currentEntityDestroyed = 0;

	GameText _winConditionText;

public:
	DestroyWave();

	void Update();

	std::string EntittyToDestroyToString(EntityToDestroyType type);

	void IncreaseEntityDestroyed(int num) { _currentEntityDestroyed += num; }
	int GetNumOfEntityToDestroy()   { return _numOfEntityToDestroy; }
	int GetCurrentEntityDestroyed() { return _currentEntityDestroyed; }
};
