#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include "core/box2DEntity.h"
#include "core/userData.h"

class Game;

class Bouncer : public Box2DEntity
{
public:
	explicit Bouncer(b2World& world_, sf::Vector2f pos_, sf::Vector2f size_);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	void createFixture(const float sizeX, const float sizeY) override;

};
