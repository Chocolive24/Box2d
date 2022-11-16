#pragma once

#include "core/DrawableObject.h"
#include "screenInterface/GameText.h"

enum class WaveType
{
	DESTROY_ENTITY,
	SURVIVE
};

class Wave
{
protected:
	WaveType _type;

	bool _started = false;
	bool _isPlaying = false;
	bool _isFinished = false;

	

public:
	Wave(WaveType type);

	bool IsFinished() { return _isFinished; }
	void SetToUnFinished() { _isFinished = false; }
};
