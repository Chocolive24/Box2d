#pragma once
#include <SFML/Graphics.hpp>

#include "Wave.h"

enum class SurviveWaveType
{
	NONE,
	CANT_MOVE = 2,
	CANT_USE_WEAPON,
	UNKNOWN
};

class SurviveWave : public Wave
{
private:
	static float _numOfSecToSurvive;
	static  float _maxNumOfSecToSurvive;
	sf::Time _currentSecSurvivded;

public:
	SurviveWave(float secondToSurvive, WaveType type);

	void Update(sf::Time elapsed);

	std::string SurviveTypeToString (WaveType type);

	static float GetNumOfSecToSurvive() { return _numOfSecToSurvive; }
	static float GetMaxNumOfSecToSurvive() { return _maxNumOfSecToSurvive; }
	sf::Time GetCurrentSecSurvivded() { return _currentSecSurvivded; }

	void update(sf::Time elapsed, Score& score) override;
	std::string StateToString() override;
	std::string WinConditionToString(WaveType type) override;
};
