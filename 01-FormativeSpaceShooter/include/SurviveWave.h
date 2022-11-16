#pragma once
#include "Wave.h"

enum class SurviveWaveType
{
	CANT_USE_WEAPON,
	CANT_MOVE,
	UNKNOWN
};

class SurviveWave : public Wave
{
private:
	float _numOfSecToSurvive;
	sf::Time _currentSecSurvivded;

public:
	SurviveWave();

	void Update(sf::Time elapsed);

	std::string SurviveTypeToString (SurviveWaveType type);

	float GetNumOfSecToSurvive() { return _numOfSecToSurvive; }
	sf::Time GetCurrentSecSurvivded() { return _currentSecSurvivded; }
};
