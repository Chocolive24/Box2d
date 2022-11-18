#pragma once

#include "Meteor.h"

#include <list>

class MetorManager : public sf::Drawable
{
private:
	Game& _game;

	std::list<Meteor> _meteors;
	std::list<MeteorExplosion> _explosions;
	int _numberOfMeteorPerSecond = 1;
	bool _mustIncreaseMeteorNum = false;

	bool _isAnExplosion = false;

	sf::Time _totalElapsed;

public:
	MetorManager(Game& game);

	void Update(sf::Time& elapsed);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::list<Meteor>& GetMeteors() { return _meteors; }
	std::list<MeteorExplosion>& GetMeteorExplosions() { return _explosions; }
};