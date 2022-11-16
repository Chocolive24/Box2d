#include "WaveManager.h"

#include <iostream>

#include "core/Properties.h"
#include "core/Utility.h"

WaveManager::WaveManager()
{
	_waveNumberText.Init("Wave number " + std::to_string(_waveNumber),
		Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 3.0f,
		60, sf::Color::Red);
}

void WaveManager::SetARandomWave()
{
	_randomWave = Utility::GetRandomInt(1, 2);
}

void WaveManager::UpdateWaveNumberText()
{
	_waveNumberText.SetString("Wave number " + std::to_string(_waveNumber));
	_waveNumberText.SetOriginToMiddle();
}

void WaveManager::Update(WaveType waveType, sf::Time elapsed)
{
	UpdateWaveNumberText();

	_titleDuration += elapsed;

	if (_titleDuration.asSeconds() >= 3.0f)
	{
		_mustDisplayTitle = false;
		_titleDuration = sf::Time::Zero;
	}

	if (waveType == WaveType::DESTROY_ENTITY)
	{
		_winConditionText.Init("DESTROY " + 
			_destroyWave.EntittyToDestroyToString(EntityToDestroyType::METEOR),
			Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 2.5f,
			30, sf::Color::Red);

		if (!_destroyWave.IsFinished())
		{
			_destroyWave.Update();
		}

		else
		{
			_mustDisplayTitle = true;
		}
	}

	else if (waveType == WaveType::SURVIVE)
	{
		_winConditionText.Init("SURVIVE " + 
			_surviveWave.SurviveTypeToString(SurviveWaveType::CANT_USE_WEAPON),
			Properties::WINDOW_WIDTH / 2.0f, Properties::WINDOW_HEIGHT / 2.5f,
			30, sf::Color::Red);

		if (!_surviveWave.IsFinished())
		{
			_surviveWave.Update(elapsed);
		}

		else
		{
			_mustDisplayTitle = true;
		}
	}
}

void WaveManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_mustDisplayTitle)
	{
		target.draw(_waveNumberText);
		target.draw(_winConditionText);
	}
}
