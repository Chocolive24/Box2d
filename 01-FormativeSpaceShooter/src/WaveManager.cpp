#include "WaveManager.h"

#include <iostream>

#include "Player.h"
#include "core/Properties.h"
#include "core/Utility.h"

WaveManager::WaveManager(Player& player) : _player(player)
{
	_randomWave = 0;
}

void WaveManager::StartARandomWave()
{
	_randomWave = Utility::GetRandomInt(1, 2);

	_waveNumber++;

	b2Vec2 startPos = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH / 2.0f, 
		Properties::WINDOW_HEIGHT / 2.0f));

	_player.SetPosition(startPos.x, startPos.y);

	_titleDuration = sf::Time::Zero;
	_isTitleTimeDone = false;

	if (_randomWave == (int)EntityToDestroyType::METEOR)
	{
		int numberEntity = DestroyWave::GetNumOfEntityToDestroy();

		if (DestroyWave::GetNumOfEntityToDestroy() < DestroyWave::GetMaxNumOfEntityToDestroy())
		{
			numberEntity += 5;
		}
		_wave = new DestroyWave(numberEntity, WaveType::DESTROY_METEOR);
	}

	else if (_randomWave == 2)
	{
		float numberOfSecond = SurviveWave::GetNumOfSecToSurvive();

		if (SurviveWave::GetNumOfSecToSurvive() < SurviveWave::GetMaxNumOfSecToSurvive())
		{
			numberOfSecond += 10;
		}

		_wave = new SurviveWave(numberOfSecond, WaveType::CANT_MOVE);
	}

}



void WaveManager::Update(sf::Time elapsed, Score& score)
{
	_titleDuration += elapsed;

	if (_titleDuration.asSeconds() >= Properties::TITLE_WAVE_TIME)
	{
		_wave->update(elapsed, score);

		_isTitleTimeDone = true;
	}
}

std::string WaveManager::GetWaveStateToString()
{
	return _wave->StateToString();
}

bool WaveManager::IsWaveFinished()
{
	if (_wave == nullptr)
	{
		return  true;
	}

	else
	{
		return !_wave->IsStarted();
	}
}

void WaveManager::IncreaseEntityDestroyed()
{
	DestroyWave* destroyWavPtr =dynamic_cast<DestroyWave*>(_wave);

	if (destroyWavPtr != nullptr)
	{
		destroyWavPtr->IncreaseEntityDestroyed();
	}

	else
	{
		std::cout << " This way is not a destroy wave." << std::endl;
	}
}

std::string WaveManager::GetWinConditionToString(WaveType type)
{
	return _wave->WinConditionToString(type);
}

