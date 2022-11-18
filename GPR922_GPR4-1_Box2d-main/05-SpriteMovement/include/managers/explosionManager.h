#pragma once

#include <vector>
#include <box2d/b2_world.h>
#include <SFML/Graphics/Drawable.hpp>

#include "core/SFML_Utilities.h"

#include "BombExplosion.h"
#include "managers/Sound.h"

class ExplosionManager : public sf::Drawable {

private:
	std::vector<std::unique_ptr<BombExplosion>> m_explosions;
	b2World& m_world;

public:
	ExplosionManager(b2World& world_);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void AddExplosion(sf::Vector2f);

};
