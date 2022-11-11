#pragma once

#include "box2d/b2_world_callbacks.h"

class Game;

class ContactListener : public b2ContactListener
{
private:
	Game& _game;

public:
	ContactListener(Game& game);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};