#pragma once
#include <box2d/b2_settings.h>

class Player;
class Meteor;
class Bomb;
class Laser;
class Explosion;


enum class UserDataType
{
	NONE = 1,
	PLAYER,
	LASER,
	BOMB,
	METEOR,
	EXPLOSION
};

class UserData 
{
private:
	UserDataType _type;
	Player* _player = nullptr;
	Meteor* _meteor = nullptr;
	Bomb* _bomb = nullptr;
	Laser* _laser = nullptr;
	Explosion* _explosion = nullptr;


public:
	UserData(Player& player) :
		_type(UserDataType::PLAYER),
		_player(&player)
	{

	}

	UserData(Meteor& meteor) :
		_type(UserDataType::METEOR),
		_meteor(&meteor)
	{

	}

	UserData(Bomb& bomb) :
		_type(UserDataType::BOMB),
		_bomb(&bomb)
	{

	}

	UserData(Laser& laser) :
		_type(UserDataType::LASER),
		_laser(&laser)
	{

	}

	UserData(Explosion& explosion) :
		_type(UserDataType::EXPLOSION),
		_explosion(&explosion)
	{

	}

	Player* GetPlayer() { return _player; }
	Meteor* GetMeteor() { return _meteor; }
	Bomb* GetBomb() { return _bomb; }
	Laser* GetLaser() { return _laser; }
	Explosion* GetExplosion() { return _explosion; }

	UserDataType GetType() { return _type; }
	void SetType(UserDataType type) { _type = type; }
};
