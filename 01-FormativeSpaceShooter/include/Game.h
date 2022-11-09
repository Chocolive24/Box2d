#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "Player.h"
#include <SFML/Graphics.hpp>


#include "Button.h"
#include "ContactListener.h"
#include "Laser.h"
#include "Meteor.h"

class Game
{
private:
	sf::RenderWindow _window;

	b2Vec2 _gravity;
	b2World _world;

	ContactListener _contactListener;

	Player _player;

	std::vector<Meteor*> _meteors;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	std::vector<sf::Sprite> _background;

	Button _startButton;
	Button _exitButton;

	bool _start = false;

public:

	Game();

	void Init();

	void CreateBackground();

	void AddMeteors();

	void CheckInput();

	void Update();

	void Draw();

	int GameLoop();
};
