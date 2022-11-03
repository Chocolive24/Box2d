#include "contact_listener.h"


MyContactListener::MyContactListener(Game& game) : game_(game)
{

}

void MyContactListener::BeginContact(b2Contact* contact)
{
    std::cout << "Contact Begin!";

    //obtain Ball pointer from user data
    mySensor* sensorA = reinterpret_cast<mySensor*>(contact->GetFixtureA()->GetUserData().pointer);
    if (sensorA != NULL) {
        std::cout << "with a sensor [A contact]";
        // Treat contact in bouncer class
        sensorA->setColor(sf::Color::Yellow);
    }
    mySensor* sensorB = reinterpret_cast<mySensor*>(contact->GetFixtureB()->GetUserData().pointer);
    if (sensorB != NULL) {
        std::cout << "with a sensor [B contact]";
        // Treat contact in bouncer class
        sensorB->setColor(sf::Color::Yellow);
    }
    std::cout << std::endl;

    //UserData* dataA = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetUserData().pointer);
    //UserData* dataB = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetUserData().pointer);
    //game_.BeginContact(dataA->userData, dataB->userData);
}

void MyContactListener::EndContact(b2Contact* contact)
{
    //UserData* dataA = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetUserData().pointer);
    //UserData* dataB = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetUserData().pointer);
    //game_.EndContact(dataA->userData, dataB->userData);
    std::cout << "Contact End!";
        //obtain Ball pointer from user data
    mySensor* sensorA = reinterpret_cast<mySensor*>(contact->GetFixtureA()->GetUserData().pointer);
    if (sensorA != NULL) {
        std::cout << "with a bouncer [A contact]";
        // Treat contact in bouncer class
        sensorA->setColor(sf::Color::Cyan);
    }
    mySensor* sensorB = reinterpret_cast<mySensor*>(contact->GetFixtureB()->GetUserData().pointer);
    if (sensorB != NULL) {
        std::cout << "with a bouncer [B contact]";
        // Treat contact in bouncer class
        sensorB->setColor(sf::Color::Cyan);
    }
    std::cout << std::endl;
}
