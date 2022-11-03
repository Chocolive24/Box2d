
#include <iostream>

#include "ball.h"
#include "game.h"

Ball::Ball(Game& game_, sf::RenderWindow& window_) : game(game_), window(window_)
{
}

void Ball::init() {

    // Defining the shape
	shape.setRadius(20.0f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
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
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);

}

void Ball::update() {
    
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

void Ball::setPixelsPosition(sf::Vector2f _pixelsPosition, sf::Vector2f velocity_) {

    float magicNumber = 3.0f;

    // Put in mouse position
    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
    // Reset the velocity (Speed)
    b2Vec2 newb2Velocity = game.pixelsToMeters(Vector2f(magicNumber * velocity_.x, magicNumber * velocity_.y));
    body->SetLinearVelocity(newb2Velocity);
}