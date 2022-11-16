#include "screenInterface/DestroyWaveUI.h"

#include "core/Properties.h"

void DestroyWaveUI::Init(WaveManager& waveManager)
{
	_winConditionUI.Init(std::to_string(waveManager.GetDestroyWave().GetCurrentEntityDestroyed()) 
		+ " / " + std::to_string(waveManager.GetDestroyWave().GetNumOfEntityToDestroy()),
		Properties::WINDOW_WIDTH / 2.0f,
		Properties::WINDOW_HEIGHT * 0.036f, 30, Properties::GREEN);

	_entitiyToDestroyUI.InitSprite("data/sprites/PNG/Meteors/meteorBrown_big1.png");
	_entitiyToDestroyUI.scale(0.25f, 0.25);
}

void DestroyWaveUI::Update(WaveManager& waveManager)
{
	_winConditionUI.SetString(std::to_string(waveManager.GetDestroyWave().GetCurrentEntityDestroyed())
		+ " / " + std::to_string(waveManager.GetDestroyWave().GetNumOfEntityToDestroy()));

	_winConditionUI.SetOriginToMiddle();

	_entitiyToDestroyUI.setPosition(Properties::WINDOW_WIDTH / 2.0f + 
		_winConditionUI.GetLocalBounds().width, 
		Properties::WINDOW_HEIGHT * 0.038f);
}

void DestroyWaveUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_winConditionUI);
	target.draw(_entitiyToDestroyUI);
}
