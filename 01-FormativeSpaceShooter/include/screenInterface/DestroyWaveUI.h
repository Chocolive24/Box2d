#pragma once
#include <SFML/Graphics.hpp>

#include "GameText.h"
#include "WaveManager.h"
#include "core/GameObject.h"

class DestroyWaveUI : public sf::Drawable
{
private:

	GameText _winConditionUI;

	GameObject _entitiyToDestroyUI;

public:
	void Init (WaveManager& waveManager);

	void Update(WaveManager& waveManager);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
