#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "Player.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow _window;

	b2Vec2 _gravity;
	b2World _world;

	Player _player;

	sf::Texture _backgroundTexture;
	sf::Sprite _background;

public:

	Game();

	void Init();

	void CheckInput();

	void Update();

	void Draw();

	int GameLoop();
};