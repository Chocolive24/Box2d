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
#include "screenInterface/Animations.h"
#include "screenInterface/BombUI.h"
#include "screenInterface/Life.h"
#include "screenInterface/LifeBar.h"
#include "screenInterface/Score.h"
#include "screenInterface/Shop.h"
#include "soundDesign/SoundManager.h"
#include "screenInterface/Edge.h"

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
	std::list<BombUI> _bombsUI;
	BombUI _bombUIManager;
	int _spaceWidth = 0;
	bool _updateBombsUI = false;
	Score _score;

	std::list<Meteor> _meteors;
	std::list<Explosion> _explosions;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	std::vector<sf::Sprite> _background;

	std::list<Edge> _edges;

	Button _startButton;
	Button _exitButton;
	Button _gameOverButton;
	Button _restartButton;

	Shop _shop;
	bool _shopOpen = false;

	bool _start = false;
	bool _isPlayerDead = false;
	bool _isPlayerCollidingMeteor = false;
	bool _isDieAnimationFinished = true;

	sf::Clock _clock;
	sf::Time _totalElapsed;
	sf::Time _elapsed;
	sf::Time _dieAnimationTime;

	Animations _animationManager;
	SoundManager _soundManager;

public:

	Game();

	b2World& GetWorld() { return _world; }
	Player& GetPlayer() { return _player; }
	Score& GetScore() { return _score; }
	Animations& GetAnimationManager() { return _animationManager; }
	sf::Time& GetElapsedTime() { return _elapsed; }

	bool IsPlayerDead() { return _isPlayerDead; }
	void SetPlayerToDead() { _isPlayerDead = true; }

	void SetPlayerToCollidingMeteor() { _isPlayerCollidingMeteor = true; }

	void Init();

	void CreateBackground();

	void AddMeteors();
	void AddBombsUI();

	void CheckInput();

	void UpdateGame(sf::Time elapsed);
	void UpdateGameObjects(sf::Time elapsed);

	void Render();

	void Restart();

	int GameLoop();
};
