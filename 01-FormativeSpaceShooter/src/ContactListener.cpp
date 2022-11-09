#include "ContactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "Meteor.h"
#include "Player.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin contact" << std::endl;

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	auto userDataA = static_cast<UserDataType>(bodyA->GetFixtureList()->GetFilterData().groupIndex);
	auto userDataB = static_cast<UserDataType>(bodyB->GetFixtureList()->GetFilterData().groupIndex);

	auto aPointer = contact->GetFixtureA()->GetUserData().pointer;
	auto bPointer = contact->GetFixtureB()->GetUserData().pointer;

	if (userDataA == UserDataType::PLAYER && userDataB == UserDataType::METEOR)
	{
		auto* player = reinterpret_cast<Player*>(aPointer);
		//auto* gameObjectB = reinterpret_cast<GameObject*>(bPointer);
		//Player* player = reinterpret_cast<Player*>(userDataA);
		std::cout << "A is a Player" << std::endl;
		std::cout << "B is a Meteor" << std::endl;
		player->SetNewColor();
		player->SetDamage(20);
	}

	else if (userDataA == UserDataType::METEOR && userDataB == UserDataType::PLAYER)
	{
		std::cout << "A is a Meteor" << std::endl;
		std::cout << "B is a Player" << std::endl;
		auto* player = reinterpret_cast<Player*>(bPointer);
		player->SetDamage(20);
	}

	/*if(laser != nullptr && meteor != nullptr)
	{
		std::cout << "A is a Laser" << std::endl;
		std::cout << "B is a Meteor" << std::endl;
	}*/

	//player = reinterpret_cast<Player*>(userDataB.pointer);
	//if (player != nullptr)
	//{
	//	std::cout << "B is a Player" << std::endl;
	//	//player->SetNewColor();
	//}
}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "end contact" << std::endl;
}
