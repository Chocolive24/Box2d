#include "managers/asteroidManager.h"

#include "SFML/Graphics/Drawable.hpp"

AsteroidManager::AsteroidManager(b2World& world_) : m_world(world_)
{
	
}

void AsteroidManager::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : asteroids) {
		target.draw(*m, states);
	}
}

void AsteroidManager::update()
{
	auto asteroidRemIt = std::remove_if(
		asteroids.begin(),
		asteroids.end(),
		[](std::unique_ptr<Asteroid>& a) {return a->getIsDead(); });

	asteroids.erase(asteroidRemIt, asteroids.end());
	
	for (auto& a : asteroids) {
		a->update();
	}
}

void AsteroidManager::AddAsteroid(sf::Vector2f size)
{
	asteroids.emplace_back(std::make_unique<Asteroid>(m_world, size));
}

void AsteroidManager::putAsteroidToDeath(int idAsteroid_)
{
	// Check id, then put isDead to true
	auto asteroidFindIt = std::find_if(
		asteroids.begin(),
		asteroids.end(),
		[idAsteroid_](auto& a) {return a->getLocalId() == idAsteroid_; }
	);

	if (asteroidFindIt != asteroids.end())
	{
		asteroidFindIt->get()->setIsDead();
	}


}



