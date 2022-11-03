#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "core/SFML_Utilities.h"
#include "managers/textureManager.h"
#include "core/userData.h"

class Box2DEntity : public sf::Drawable, public sf::Transformable
{

public:
	Box2DEntity(b2World& world_);
	~Box2DEntity();

	void update();

protected:
	b2Body* m_body = nullptr;
	UserData* m_userData;

	b2World& m_world;

	TextureManager* texManager = TextureManager::Instance();

	virtual void createFixture(const float sizeX, const float sizeY) = 0;

};
