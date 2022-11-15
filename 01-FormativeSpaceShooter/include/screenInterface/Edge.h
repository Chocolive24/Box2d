#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "core/UserData.h"
#include "SFML/Graphics.hpp"

class Game;

class Edge
{
private:
	Game& _game;

	b2Body* _body = nullptr;

	UserData* _userData = nullptr;
	bool _addedToGroupIndex = false;

	b2FixtureDef _fixtureDef;

public:
	Edge(Game& game, sf::Vector2f v1, sf::Vector2f v2);
};
