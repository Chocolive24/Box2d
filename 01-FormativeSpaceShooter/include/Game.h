#pragma once

#include <box2d/b2_world.h>
#include "Player.h"



#include "screenInterface/Button.h"
#include "core/ContactListener.h"
#include "Meteor.h"
#include <list>

#include "Wave/WaveManager.h"
#include "screenInterface/Animations.h"
#include "screenInterface/Shop.h"
#include "soundDesign/Sound.h"
#include "screenInterface/Edge.h"
#include "screenInterface/Menu.h"
#include "screenInterface/UIManager.h"
#include "soundDesign/Music.h"
#include "MeteorManager.h"

class Game
{
private:
	sf::RenderWindow _window;

	b2Vec2 _gravity;
	b2World _world;

	ContactListener _contactListener;

	Player _player;

	MetorManager _meteorManager;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	std::vector<sf::Sprite> _background;

	std::list<Edge> _edges;

	Shop _shop;
	bool _shopOpen = false;

	bool _start = false;

	sf::Clock _clock;
	sf::Time _elapsed;

	Menu _menuManager;
	Animations _animationManager;
	Sound _soundManager;
	Music _musicManager;

	WaveManager _waveManager;
	UIManager _uiManager;

public:
	Game();

	void Init();

	void CheckInput();
	void CheckKeyPressed();
	void CheckPollEvent();

	void UpdateGame(sf::Time& elapsed);
	void UpdateGameObjects(sf::Time& elapsed);

	void Render();

	int GameLoop();

	void Restart();

	void CreateBackground();

	bool IsStarted() { return _start; }
	bool IsShopOpen() { return _shopOpen; }
	sf::RenderWindow& GetWindow() { return _window; }
	b2World& GetWorld() { return _world; }
	Player& GetPlayer() { return _player; }
	WaveManager& GetWaveManager() { return _waveManager; }
	UIManager& GetUIManager() { return _uiManager; }
	Animations& GetAnimationManager() { return _animationManager; }
	Sound& GetSoundManager() { return _soundManager; }
	Music& GetMusicManager() { return _musicManager; }
};
