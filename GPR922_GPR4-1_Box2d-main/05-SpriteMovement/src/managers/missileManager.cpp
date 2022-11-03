#include "managers/missileManager.h"

MissileManager::MissileManager(b2World& world_) : m_world(world_)
{
}

void MissileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : m_missiles) {
		target.draw(*m, states);
	}
}

void MissileManager::update()
{
	auto missileRemIt = std::remove_if(
		m_missiles.begin(),
		m_missiles.end(),
		[](std::unique_ptr<Missile>& m) {return m->getIsDead(); });

	m_missiles.erase(missileRemIt, m_missiles.end());

	for (auto& m : m_missiles) {
		m->update();
	}
}

void MissileManager::AddMissile(Ship& ship_)
{

	sf::Vector2f startPos = ship_.getPosition();
	float angle = ship_.getRotation();

	m_missiles.emplace_back(
		std::make_unique<Missile>(
			m_world,
			startPos,
			angle)
	);
}

void MissileManager::putMissileToDeath(int idMissile_)
{
	// Check id, then put isDead to true
	auto mFintIt = std::find_if(
		m_missiles.begin(),
		m_missiles.end(),
		[idMissile_](std::unique_ptr<Missile>& m) {return m->getLocalId() == idMissile_; }
	);

	if(mFintIt != m_missiles.end())
	{
		mFintIt->get()->setIsDead();
	}

}
