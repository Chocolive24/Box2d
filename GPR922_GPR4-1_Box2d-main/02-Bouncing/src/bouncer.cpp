
#include <iostream>

#include "bouncer.h"
#include "game.h"

Bouncer::Bouncer(Game& game_, sf::RenderWindow& window_) : game(game_), window(window_)
{
}

void Bouncer::init() {

    // Defining the shape
    // 2 meters long, 0,5 meters high
    b2Vec2 physicalSize(2.0f, 0.5f);
    shape.setSize(sf::Vector2f(Game::metersToPixels(physicalSize)));
	shape.setFillColor(sf::Color::Cyan);
	shape.setFillColor(sf::Color::Cyan);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides

    b2Vec2 windowSize = Game::pixelsToMeters(sf::Vector2f(0.5f * window.getSize().x, window.getSize().y - 100.0f));
    bodyDef.position.Set(windowSize.x, windowSize.y);
    body = this->game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2PolygonShape bouncerBox;
    bouncerBox.SetAsBox(physicalSize.x, physicalSize.y);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &bouncerBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.5f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);

}

void Bouncer::update() {
    
    std::cout << "Bouncer position [" << body->GetPosition().x << ":" << body->GetPosition().y 
        << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();
    // Translate meters to pixels
    sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);
    // Set the position of the Graphic object
	shape.setPosition(graphicPosition);

}

void Bouncer::render() {
	window.draw(shape);
}

//void Bouncer::setPixelsPosition(sf::Vector2f _pixelsPosition) {
//    // Put in mouse position
//    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
//    // Reset the velocity (Speed)
//    body->SetLinearVelocity(b2Vec2_zero);
//}