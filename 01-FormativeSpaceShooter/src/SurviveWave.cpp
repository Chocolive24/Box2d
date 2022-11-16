#include "SurviveWave.h"

#include <iostream>

#include "core/Properties.h"

SurviveWave::SurviveWave() : Wave(WaveType::SURVIVE)
{
	_numOfSecToSurvive = 30.0f;
}

void SurviveWave::Update(sf::Time elapsed)
{
	if (!_started)
	{
		_numOfSecToSurvive += 5;
		_started = true;
	}

	else
	{
		_currentSecSurvivded += elapsed;

		if (_currentSecSurvivded.asSeconds() >= _numOfSecToSurvive)
		{
			_isFinished = true;
			_currentSecSurvivded = sf::Time::Zero;
		}

		if (_isFinished)
		{
			_started = false;
		}
	}
}

std::string SurviveWave::SurviveTypeToString(SurviveWaveType type)
{
	switch (type)
	{
	case SurviveWaveType::CANT_USE_WEAPON:
		return "YOU CAN'T USE WEAPONS";
	case SurviveWaveType::CANT_MOVE:
		return "YOU CAN'T MOVE";
	case SurviveWaveType::UNKNOWN:
		return "UNKNOWN";
	}
}
