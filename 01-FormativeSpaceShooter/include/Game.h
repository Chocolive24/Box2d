#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "Player.h"
#include <SFML/Graphics.hpp>


#include "screenInterface/Button.h"
#include "core/ContactListener.h"
#include "Laser.h"
#include "Meteor.h"
#include <list>

#include "Explosion.h"
#include "screenInterface/Life.h"
#include "screenInterface/LifeBar.h"
#include "screenInterface/Score.h"
#include "soundDesign/SoundManager.h"

class Game
{
private:
	sf::RenderWindow _window;

	b2Vec2 _gravity;
	b2World _world;

	ContactListener _contactListener;

	Player _player;
	LifeBar _lifeBar;
	std::list<Life> _lives;
	Score _score;

	std::list<Meteor> _meteors;
	std::list<Explosion> _explosions;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	std::vector<sf::Sprite> _background;

	Button _startButton;
	Button _exitButton;

	bool _start = false;
	bool _isPlayerDead = false;

	sf::Clock _clock;
	sf::Time _totalElapsed;

	SoundManager _soundManager;

public:

	Game();

	b2World& GetWorld() { return _world; }
	Player& GetPlayer() { return _player; }
	Score& GetScore() { return _score; }

	void SetPlayerToDead() { _isPlayerDead = true; }

	void Init();

	void CreateBackground();

	void AddMeteors();

	void UpdateLives();

	void CheckInput();

	

	void UpdateGame(sf::Time elapsed);
	void UpdateGameObjects(sf::Time elapsed);

	void Render();

	int GameLoop();
};
