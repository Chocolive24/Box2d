#include "managers/ExplosionManager.h"

ExplosionManager::ExplosionManager(b2World& world_) : m_world(world_)
{
}

void ExplosionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : m_explosions) {
		target.draw(*m, states);
	}
}

void ExplosionManager::update()
{
	auto exploRemIt = std::remove_if(
		m_explosions.begin(),
		m_explosions.end(),
		[](std::unique_ptr<Explosion>& m) {return m->getIsDead(); });

	m_explosions.erase(exploRemIt, m_explosions.end());

	for (auto& m : m_explosions) {
		m->update();
	}
}

void ExplosionManager::AddExplosion(sf::Vector startPos_)
{
	m_explosions.emplace_back(std::make_unique<Explosion>(startPos_));
}

