#include "ContactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "Meteor.h"
#include "Player.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin contact" << std::endl;

	auto userDataA = contact->GetFixtureA()->GetUserData();
	auto userDataB = contact->GetFixtureB()->GetUserData();

	Player* player = reinterpret_cast<Player*>(userDataA.pointer);
	Meteor* meteor = reinterpret_cast<Meteor*>(userDataB.pointer);
	Laser* laser = reinterpret_cast<Laser*>(userDataA.pointer);

	if (player != nullptr && meteor != nullptr)
	{
		std::cout << "A is a Player" << std::endl;
		std::cout << "B is a Meteor" << std::endl;
		//player->SetNewColor();
		player->SetDamage(20);
	}

	if(laser != nullptr && meteor != nullptr)
	{
		std::cout << "A is a Laser" << std::endl;
		std::cout << "B is a Meteor" << std::endl;
	}

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
