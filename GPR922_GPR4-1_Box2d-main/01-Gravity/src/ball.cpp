
#include <iostream>

#include "ball.h"
#include "game.h"

Ball::Ball(Game& game_, sf::RenderWindow& window_) : game(game_), window(window_)
{
}

void Ball::init() {

    // Defining the shape
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = Game::pixelsToMeters(window.getSize());
    bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);
    body = this->game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2CircleShape ballBox;
    ballBox.m_radius = Game::pixelsToMeters(shape.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &ballBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);

}

void Ball::update() {
    
    std::cout << "body position [" << body->GetPosition().x << ":" << body->GetPosition().y 
        << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();
    // Translate meters to pixels
    sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);
    // Set the position of the Graphic object
	shape.setPosition(graphicPosition);
}

void Ball::render() {
	window.draw(shape);
}

void Ball::setPixelsPosition(sf::Vector2f _pixelsPosition) {
    // Put in mouse position
    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
    // Reset the velocity (Speed)
    body->SetLinearVelocity(b2Vec2_zero);
}