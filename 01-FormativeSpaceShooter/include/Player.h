#pragma once
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>

#include "Bomb.h"
#include "Laser.h"

class Player : public sf::Drawable, public sf::Transformable
{
private:
    // -------------------------------------------------------------------------------------------
    // Ship attributes.

    // Defining the sprite
    sf::Texture _shipTexture;
    sf::Sprite _shipSprite;

    sf::Texture _fireTexture;
    sf::Sprite _fireSprite;

    // Defing the box 2D elements
    b2BodyDef _bodyDef;
    
    b2Body* _body = nullptr;

    // Shape of the physical (A box)
    b2PolygonShape _hitBox;

    // The fixture is what it defines the physic react
    b2FixtureDef _playerFixtureDef;

    // -------------------------------------------------------------------------------------------
	// Attack attributes.

    std::vector<Laser*> _lasers;
    std::vector<Bomb*> _bombs;
    int _bombNbr = 1;

    // -------------------------------------------------------------------------------------------
	// Player's data attributes.

    sf::RectangleShape _currentLifeBar;
    sf::RectangleShape _damagedLifeBar;
    float _currentLife;
    const float _maxLife = 100.0f;

    sf::Texture _livesTexture;
    sf::Sprite _livesSprite;
    int _maxLives = 3;
    std::vector<sf::Sprite> _lives;

public:
    // -------------------------------------------------------------------------------------------
    // Getters and Setters

    b2Body* GetBody() { return _body; }
    std::vector<Laser*>& GetLasers() { return _lasers; }

    void SetLinearVelocity(b2Vec2 newVelocity) { _body->SetLinearVelocity(newVelocity); }
    void SetLinearDamping(float newDamping) { _body->SetLinearDamping(newDamping); }

    // -------------------------------------------------------------------------------------------

	void Init(b2World& world);

    void InitLifeBar();
    void InitLives();

    void Move(b2Vec2 force);
    void Rotate(float omega);

    void AddLaser(b2World& world);
    void Shoot(b2World& world);
    void ThrowBomb(b2World& world);

    void Update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
