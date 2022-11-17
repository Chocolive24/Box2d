#include "core/ContactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "Game.h"
#include "Meteor.h"
#include "Player.h"
#include "core/Properties.h"

enum class UserDataType;
class UserData;
class Game;

ContactListener::ContactListener(Game& game) : _game(game)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	// ---------------------------------------------------------------------------------------------------------
	// Get the bodies of the collision.
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// ---------------------------------------------------------------------------------------------------------
	// Get the group index of the bodies.

	auto userDataA = static_cast<UserDataType>(bodyA->GetFixtureList()->GetFilterData().categoryBits);
	auto userDataB = static_cast<UserDataType>(bodyB->GetFixtureList()->GetFilterData().categoryBits);

	// ---------------------------------------------------------------------------------------------------------
	// Get the pointers of the fixture.

	auto aPointer = contact->GetFixtureA()->GetUserData().pointer;
	auto bPointer = contact->GetFixtureB()->GetUserData().pointer;

	// ---------------------------------------------------------------------------------------------------------
	// Collision between the player and the other game objects.

	// Case user data A = player.
	if (userDataA == UserDataType::PLAYER)
	{
		auto* player = reinterpret_cast<UserData*>(aPointer);

		if (userDataB == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(bPointer);

			player->GetPlayer()->TakeDamage(20);
			meteor->GetMeteor()->SetToDestroyed();
			//_game.SetPlayerToCollidingMeteor();
		}

		else if (userDataB == UserDataType::BOMB)
		{
			auto* bomb = reinterpret_cast<UserData*>(bPointer);

			player->GetPlayer()->TakeDamage(100);
			bomb->GetBomb()->SetToDestroyed();
		}
	}

	// Case user data B = player.
	else if (userDataB == UserDataType::PLAYER)
	{
		auto* player = reinterpret_cast<UserData*>(bPointer);

		if (userDataA == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(aPointer);

			player->GetPlayer()->TakeDamage(20);
			meteor->GetMeteor()->SetToDestroyed();
		}

		else if (userDataA == UserDataType::BOMB)
		{
			auto* bomb = reinterpret_cast<UserData*>(aPointer);

			bomb->GetBomb()->SetToDestroyed();
		}
	}

	// ---------------------------------------------------------------------------------------------------------
	// Collisions between the lasers and the other game objects.

	if (userDataA == UserDataType::LASER)
	{
		auto* laser = reinterpret_cast<UserData*>(aPointer);

		if (userDataB == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(bPointer);
			laser->GetLaser()->SetToDestroyed();
			meteor->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}

		else if (userDataB == UserDataType::BOMB)
		{
			auto* bomb = reinterpret_cast<UserData*>(bPointer);

			laser->GetLaser()->SetToDestroyed();
			bomb->GetBomb()->SetToDestroyed();
		}
	}

	else if(userDataB == UserDataType::LASER)
	{
		auto* laser = reinterpret_cast<UserData*>(bPointer);

		if (userDataA == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(aPointer);

			laser->GetLaser()->SetToDestroyed();
			meteor->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}

		else if (userDataA == UserDataType::BOMB)
		{
			auto* bomb = reinterpret_cast<UserData*>(aPointer);

			laser->GetLaser()->SetToDestroyed();
			bomb->GetBomb()->SetToDestroyed();
		}
	}

	// ---------------------------------------------------------------------------------------------------------
	// Collisions between the bombs and the other game objects.

	if (userDataA == UserDataType::BOMB)
	{
		auto* bomb = reinterpret_cast<UserData*>(aPointer);

		if (userDataB == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(bPointer);

			bomb->GetBomb()->SetToDestroyed();
			meteor->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}
	}

	else if (userDataB == UserDataType::BOMB)
	{
		auto* bomb = reinterpret_cast<UserData*>(bPointer);

		if (userDataA == UserDataType::METEOR)
		{
			auto* meteor = reinterpret_cast<UserData*>(aPointer);

			bomb->GetBomb()->SetToDestroyed();
			meteor->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}
	}

	// ---------------------------------------------------------------------------------------------------------
	// Collisions between the meteors and the other game objects.

	if (userDataA == UserDataType::METEOR)
	{
		auto* meteorA = reinterpret_cast<UserData*>(aPointer);

		if (userDataB == UserDataType::METEOR)
		{
			auto* meteorB = reinterpret_cast<UserData*>(bPointer);

			meteorA->GetMeteor()->SetToDestroyed();
			meteorB->GetMeteor()->SetToDestroyed();
		}

		else if (userDataB == UserDataType::EXPLOSION)
		{
			auto* explosion = reinterpret_cast<UserData*>(bPointer);

			meteorA->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}
	}

	else if (userDataB == UserDataType::METEOR)
	{
		auto* meteor = reinterpret_cast<UserData*>(bPointer);

		if (userDataA == UserDataType::EXPLOSION)
		{
			auto* explosion = reinterpret_cast<UserData*>(aPointer);

			meteor->GetMeteor()->SetToDestroyed();
			_game.GetUIManager().GetScore().IncreaseScore(Properties::METEOR_POINTS);
			_game.GetWaveManager().IncreaseEntityDestroyed();
		}
	}
	// The other meteors collisions are already handled
}

void ContactListener::EndContact(b2Contact* contact)
{
	// ---------------------------------------------------------------------------------------------------------
	// Get the bodies of the collision.
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// ---------------------------------------------------------------------------------------------------------
	// Get the group index of the bodies.

	auto userDataA = static_cast<UserDataType>(bodyA->GetFixtureList()->GetFilterData().categoryBits);
	auto userDataB = static_cast<UserDataType>(bodyB->GetFixtureList()->GetFilterData().categoryBits);

	// ---------------------------------------------------------------------------------------------------------
	// Get the pointers of the fixture.

	auto aPointer = contact->GetFixtureA()->GetUserData().pointer;
	auto bPointer = contact->GetFixtureB()->GetUserData().pointer;

	// ---------------------------------------------------------------------------------------------------------
	// Collisions between the lasers and the other game objects.

	if (userDataA == UserDataType::LASER)
	{
		auto* laser = reinterpret_cast<UserData*>(aPointer);

		if (userDataB == UserDataType::EDGE)
		{
			laser->GetLaser()->SetToDestroyed();
		}
	}

	else if (userDataB == UserDataType::LASER)
	{
		auto* laser = reinterpret_cast<UserData*>(bPointer);

		if (userDataA == UserDataType::EDGE)
		{
			laser->GetLaser()->SetToDestroyed();
		}
	}
}
