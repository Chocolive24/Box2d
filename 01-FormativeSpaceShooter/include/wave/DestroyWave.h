#pragma once
#include "Wave.h"
#include "core/GameObject.h"
#include "screenInterface/GameText.h"

enum class EntityToDestroyType
{
	NONE,
	METEOR,
	
};

class DestroyWave : public Wave
{
private:
	EntityToDestroyType _type;

	static int _numOfEntityToDestroy;
	static int _maxNumOfEntityToDestroy;
	int _currentEntityDestroyed = 0;

	GameText _winConditionText;

public:
	

	DestroyWave(int numOfEntity, WaveType type);

	void update(sf::Time& elapsed, Score& score) override;

	std::string EntittyToDestroyToString(WaveType type);

	void IncreaseEntityDestroyed() { _currentEntityDestroyed++; }
	EntityToDestroyType& GetEntityType() { return _type; }
	static int GetNumOfEntityToDestroy() { return _numOfEntityToDestroy; }
	static int GetMaxNumOfEntityToDestroy() { return _maxNumOfEntityToDestroy; }
	int GetCurrentEntityDestroyed() { return _currentEntityDestroyed; }

	std::string StateToString() override;
	std::string WinConditionToString(WaveType type) override;
};
