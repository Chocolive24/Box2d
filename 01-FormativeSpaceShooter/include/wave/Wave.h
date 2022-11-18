#pragma once
#include <xstring>
#include <SFML/Graphics.hpp>

#include "screenInterface/Score.h"

enum class WaveType
{
	NONE,
	DESTROY_METEOR,
	CANT_MOVE,
	CANT_USE_WEAPON
};

class Wave
{
protected:
	WaveType _type;

	bool _started = false;

public:
	Wave(WaveType type);

	virtual void update(sf::Time& elapsed, Score& score) = 0;

	bool IsStarted() { return _started; }
	WaveType GetWaveType() { return _type; }


	virtual std::string StateToString() = 0;
	virtual std::string WinConditionToString(WaveType type) = 0;
};
