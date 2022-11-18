#pragma once

#include "weapon/Bomb.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "core/GameObject.h"
#include "weapon/Laser.h"
#include <SFML/Graphics.hpp>

#include <list>

class Game;

class Player : public GameObject
{
private:
    Game& _game;

    // Shape of the physical (A box)
    b2PolygonShape _hitBox;

    // -------------------------------------------------------------------------------------------
	// Attack attributes.

    std::list<Laser> _lasers;
    std::list<Bomb> _bombs;
    int _bombNbr = 1;

    // -------------------------------------------------------------------------------------------
	// Player's data attributes.

    b2Vec2 _startPosition;

    int _currentLife;
    int _maxLife = 100;

    int _maxLives = 3;

    const float _rotationSpeed = 40.0f;

    bool _canBeControlled = true;
    bool _canShoot = true;
    sf::Time _lastShotDuration;
    bool _canThrowBomb = true;
    sf::Time _lastBombDuration;

    bool _isInvincible = false;
    sf::Time _invicibiltyDuration;
    bool _isDead = false;

    // -------------------------------------------------------------------------------------------

public:
    Player(Game& game);

    // -------------------------------------------------------------------------------------------
    // Moving methods.

    void Move(b2Vec2 force);
    void Rotate(float degreesAngle);

    // -------------------------------------------------------------------------------------------
    // Attack methods.

    void Shoot(int level);
    void ThrowBomb(b2World& world);

    // -------------------------------------------------------------------------------------------
    // Graphical methods.

    void update(sf::Time& elapsed) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // -------------------------------------------------------------------------------------------
    // Getters and Setters.

    b2Body* GetBody() { return _body; }

    void SetPosition(float x, float y) { _body->SetTransform(b2Vec2(x, y), 0.0f); }
    sf::Vector2f GetFrontPosition() const;
    float GetDeltaAngle(float angle);
    void SetLinearVelocity(b2Vec2 newVelocity) { _body->SetLinearVelocity(newVelocity); }

    int GetBombNbr() { return _bombNbr; }
    void SetBombNumber(int nbr) { _bombNbr += nbr; }

    bool CanBeControlled() { return _canBeControlled; }
    void SetControl(bool canBeControlled) { _canBeControlled = canBeControlled; }

    bool IsInvincible() { return _isInvincible; }
    void SetInvincibility(bool isInvicible) { _isInvincible = isInvicible; }

    bool IsDead() { return _isDead; }
    void SetToDead() { _isDead = true; }

    void SetNewLife(int nbr) { _maxLife += nbr; _currentLife += nbr; }
    int GetCurrentLife() { return _currentLife; }
    int GetMaxLife() { return _maxLife; }
    int GetMaxLives() { return _maxLives; }
    void SetCurrentLifeToMax() { _currentLife = _maxLife; }
    void TakeDamage(int damage) { _currentLife -= damage; }

    bool CanShoot() { return _canShoot; }
    void SetCanShootToFalse() { _canShoot = false; }
    bool CanThrowBomb() { return _canThrowBomb; }

    std::list<Laser>& GetLasers() { return _lasers; }
    std::list<Bomb>& GetBombs() { return _bombs; }
    void SetLinearDamping(float damping) { _body->SetLinearDamping(damping); }

    // -------------------------------------------------------------------------------------------
};