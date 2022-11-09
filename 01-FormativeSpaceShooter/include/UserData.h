#pragma once
#include <box2d/b2_settings.h>

enum class UserDataType
{
	NONE = 1,
	PLAYER,
	LASER,
	BOMB,
	METEOR
};

class UserData 
{
private:
	UserDataType _type;

public:
	UserData();

	UserDataType GetType() { return _type; }
	void SetType(UserDataType type) { _type = type; }
};
