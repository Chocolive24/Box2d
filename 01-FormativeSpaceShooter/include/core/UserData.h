#pragma once
#include <box2d/b2_settings.h>

class Player;
class Meteor;
class Bomb;
class Laser;
class BombExplosion;
class Edge;

enum class UserDataType
{
	PLAYER = 0x0001,
	LASER = 0x0002,
	BOMB = 0x0004,
	METEOR = 0x0008,
	EDGE = 0x0010,
	EXPLOSION = 0x0020,
};

class UserData 
{
private:
	UserDataType _type;
	Player* _player = nullptr;
	Meteor* _meteor = nullptr;
	Bomb* _bomb = nullptr;
	Laser* _laser = nullptr;
	BombExplosion* _explosion = nullptr;
	Edge* _edge = nullptr;


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

	UserData(BombExplosion& explosion) :
		_type(UserDataType::EXPLOSION),
		_explosion(&explosion)
	{

	}

	UserData(Edge& edge) :
		_type(UserDataType::EDGE),
		_edge(&edge)
	{
		
	}

	Player* GetPlayer() { return _player; }
	Meteor* GetMeteor() { return _meteor; }
	Bomb* GetBomb() { return _bomb; }
	Laser* GetLaser() { return _laser; }
	BombExplosion* GetExplosion() { return _explosion; }
	Edge* GetEdge() { return _edge; }

	UserDataType GetType() { return _type; }
	void SetType(UserDataType type) { _type = type; }
};