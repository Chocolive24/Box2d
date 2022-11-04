#pragma once
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
    

    // Defining the sprite
    //sf::RectangleShape _shape;

    sf::Texture _texture;
    sf::Sprite _sprite;

    // Defing the box 2D elements
    b2BodyDef _bodyDef;
    
    b2Body* _body = nullptr;

    // Shape of the physical (A box)
    b2PolygonShape _box;

    // The fixture is what it defines the physic react
    b2FixtureDef _playerFixtureDef;



public:

    // -------------------------------------------------------------------------------------------
    // Getters and Setters

    void SetLinearVelocity(b2Vec2 newVelocity) { _body->SetLinearVelocity(newVelocity); }
    void SetLinearDamping(float newDamping) { _body->SetLinearDamping(newDamping); }

    // -------------------------------------------------------------------------------------------

	void Init(b2World& world);

    void Move(b2Vec2 force);

    void Update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
