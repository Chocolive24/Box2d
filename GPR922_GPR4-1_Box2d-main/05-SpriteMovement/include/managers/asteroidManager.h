#pragma once


#include <vector>

#include <box2d/b2_world.h>
#include "SFML/Graphics/Drawable.hpp"

#include "asteroid.h"

class AsteroidManager : public sf::Drawable
{

private:
	std::vector<std::unique_ptr<Asteroid>> asteroids;
	b2World& m_world;
		
public:
	AsteroidManager(b2World& m_world_);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void AddAsteroid(sf::Vector2f size);
	void putAsteroidToDeath(int idAsteroid_);

};