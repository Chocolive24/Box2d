#include "Wave/SurviveWave.h"

#include <iostream>

#include "core/Properties.h"
#include "screenInterface/GameText.h"

float SurviveWave::_numOfSecToSurvive;
float SurviveWave::_maxNumOfSecToSurvive = 30;

SurviveWave::SurviveWave(float secondToSurvive, WaveType type) : Wave(type)
{
	_numOfSecToSurvive = secondToSurvive;
}

std::string SurviveWave::SurviveTypeToString(WaveType type)
{
	
	if (type == WaveType::CANT_MOVE)
	{
		return "YOU CAN'T MOVE";
	}
		
	if (type == WaveType::CANT_USE_WEAPON) 
	{
		return "YOU CAN'T USE WEAPONS";
	}
		
	else
	{
		return "NONE";
	}
}

void SurviveWave::update(sf::Time elapsed, Score& score)
{
	_currentSecSurvivded += elapsed;

	if (_currentSecSurvivded.asSeconds() >= _numOfSecToSurvive)
	{
		_started = false;
	}
}

std::string SurviveWave::StateToString()
{
	std::string string;

	string += std::to_string(static_cast<int>(_currentSecSurvivded.asSeconds()));

	string += " Sec";

	string += " / ";

	string += std::to_string(static_cast<int>(_numOfSecToSurvive));

	string += " Sec";

	return string;
}

std::string SurviveWave::WinConditionToString(WaveType type)
{
	std::string string;

	string += "SURVIVE ";

	string += SurviveTypeToString(type);

	return string;
}
