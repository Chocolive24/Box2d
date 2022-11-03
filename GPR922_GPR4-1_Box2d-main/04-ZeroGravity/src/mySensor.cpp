
#include <iostream>
#include <math.h>

#include "mySensor.h"
#include "game.h"
#include "SFML_Utilities.h"

mySensor::mySensor(Game& game_, RenderWindow& window_, Vector2f pos_, int radius_) : game(game_), window(window_)
{
    init(pos_, radius_);
}

void mySensor::init(Vector2f pos_, int radius_) {

    // Defining the shape
    shape.setPosition(pos_);
    shape.setOrigin(radius_, radius_);
    shape.setRadius(radius_);
	shape.setFillColor(sf::Color::Cyan);
	shape.setFillColor(sf::Color::Cyan);
    //shape.setRotation(45.0f);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    bodyDef.position.Set(Game::pixelsToMeters(shape.getPosition()).x, Game::pixelsToMeters(shape.getPosition()).y);
    //float worldAngle = SFML_Utilities::vecAngle(Vector2f(1.0f, 0.0f), mouseLine);
    //bodyDef.angle = -1.0f * worldAngle;
    bodyDef.angle = 0.0f;
    body = this->game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2CircleShape shapeBox;
    //bouncerBox.SetAsBox(physicalSize.x, physicalSize.y);
    shapeBox.m_radius = Game::pixelsToMeters(shape.getRadius());
    //bouncerBox.SetAsBox(
    //    0.5f * Game::pixelsToMeters(shape.getRadius()),
    //    0.5f * Game::pixelsToMeters(shape.getRadius()),
    //    b2Vec2_zero,
    //    SFML_Utilities::degToRad(.0f));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &shapeBox;
    //playerFixtureDef.isSensor = true;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.2f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(this);
    body->CreateFixture(&playerFixtureDef);

}

void mySensor::update() {

    //std::cout << "mySensor position [" << body->GetPosition().x << ":" << body->GetPosition().y
    //    << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;

    const auto& b2Position = body->GetPosition();
    shape.setPosition(Game::metersToPixels(b2Position));
    const auto b2rotation = body->GetAngle();
    shape.setRotation(-1.0f * radToDeg(b2rotation));

}

void mySensor::render() {
	window.draw(shape);
}

void mySensor::setColor(sf::Color color_)
{
    shape.setFillColor(color_);
}
