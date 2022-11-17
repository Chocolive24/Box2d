#pragma once
#include "DestroyWave.h"
#include "SurviveWave.h"
#include "screenInterface/GameText.h"

class WaveManager
{
private:
	Wave* _wave = nullptr;

	Player& _player;

	int _waveNumber = 0;

	int _randomWave;

	sf::Time _titleDuration;
	bool _isTitleTimeDone = false;

public:
	WaveManager(Player& player);

	void StartARandomWave();


	void Update(sf::Time elapsed, Score& score);

	int GetRandomWaveNumber() { return _randomWave; }

	int GetWaveNumber() { return _waveNumber; }
	WaveType GetWaveType() { return  _wave->GetWaveType(); }
	std::string GetWaveStateToString();
	bool IsWaveFinished();
	bool IsTitleTimeDone() { return _isTitleTimeDone; }
	void IncreaseEntityDestroyed();
	std::string GetWinConditionToString(WaveType type);
};
