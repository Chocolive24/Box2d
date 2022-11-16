#pragma once
#include "DestroyWave.h"
#include "SurviveWave.h"

class WaveManager : public sf::Drawable
{
private:
	DestroyWave _destroyWave;
	SurviveWave _surviveWave;

	int _waveNumber = 1;

	GameText _waveNumberText;
	GameText _winConditionText;

	bool _mustDisplayTitle = true;

	sf::Time _titleDuration;

	int _randomWave;

	bool _isRandomWaveSetUp = false;


public:
	WaveManager();

	bool IsRandomWaveSetUp() { return _isRandomWaveSetUp; }
	void SetRandomWaveToSetUp() { _isRandomWaveSetUp = true; }
	void SetRandomWaveToNotSetUp() { _isRandomWaveSetUp = false; }
	void SetARandomWave();
	int GetTheRandomWave() { return  _randomWave; }

	void Update(WaveType waveType, sf::Time elapsed);
	void UpdateWaveNumberText();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	DestroyWave& GetDestroyWave() { return _destroyWave; }
	SurviveWave& GetSurviveWave() { return _surviveWave; }
};
