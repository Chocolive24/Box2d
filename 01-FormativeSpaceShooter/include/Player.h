#pragma once
#include <list>
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SFML/Graphics.hpp>

#include "Bomb.h"
#include "core/GameObject.h"
#include "Laser.h"

class Game;

class Player : public GameObject
{
private:
    Game& _game;

    sf::Texture _fireTexture;
    sf::Sprite _fireSprite;

    // Shape of the physical (A box)
    b2PolygonShape _hitBox;

    // -------------------------------------------------------------------------------------------
	// Attack attributes.

    std::list<Laser> _lasers;
    std::list<Bomb> _bombs;
    int _bombNbr = 3;

    // -------------------------------------------------------------------------------------------
	// Player's data attributes.

    b2Vec2 _startPosition;

    int _currentLife;
    int _maxLife = 100;

    int _lives = 3;

    bool _canShoot = true;
    sf::Time _lastShotDuration;

public:
    Player(Game& game);

    // -------------------------------------------------------------------------------------------
    // Getters and Setters

    b2Body* GetBody() { return _body; }

    void SetLinearVelocity(b2Vec2 newVelocity) { _body->SetLinearVelocity(newVelocity); }
    void SetLinearDamping(float newDamping) { _body->SetLinearDamping(newDamping); }


    int GetCurrentLife() { return _currentLife; }
    int GetMaxLife() { return _maxLife; }
    int GetLives() { return _lives; }
    bool CanShoot() { return _canShoot; }
    void SetCanShootToFalse() { _canShoot = false; }

    void SetCurrentLifeToMax() { _currentLife = _maxLife; }
    void TakeDamage(int damage) { _currentLife -= damage; }

    // -------------------------------------------------------------------------------------------

	void Init(b2World& world);

    void InitLifeBar();
    void InitLives();

    void Move(b2Vec2 force);
    void Rotate(float omega);

    void AddLaser(b2World& world);
    void Shoot(b2World& world);
    void ThrowBomb(b2World& world);

    void update(sf::Time elapsed) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
