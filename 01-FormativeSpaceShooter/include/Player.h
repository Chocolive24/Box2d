#pragma once

#include "Bomb.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include "core/GameObject.h"
#include "Laser.h"
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
    Explosion _bombExplosion;
    bool _isAnExplosion = false;

    // -------------------------------------------------------------------------------------------
	// Player's data attributes.

    b2Vec2 _startPosition;

    int _currentLife;
    int _maxLife = 100;

    int _maxLives = 3;

    bool _canMove = true;
    bool _canShoot = true;
    sf::Time _lastShotDuration;

    bool _isDead = false;

    // -------------------------------------------------------------------------------------------

public:
    Player(Game& game);

    // -------------------------------------------------------------------------------------------
    // Moving methods.

    void Move(b2Vec2 force);
    void Rotate(float omega);

    // -------------------------------------------------------------------------------------------
    // Attack methods.

    void Shoot(int level);
    void ThrowBomb(b2World& world);

    // -------------------------------------------------------------------------------------------
    // Graphical methods.

    void update(sf::Time elapsed) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // -------------------------------------------------------------------------------------------
    // Methods to add lasers.

    void AddLaserLvl1(float spriteWidth);
    void AddLaserLvl2(float spriteWidth);
    void AddLaserLvl3(float spriteWidth);
    void AddLaserLvl4(float spriteWidth);
    void AddLaserLvl5(float spriteWidth);

    // -------------------------------------------------------------------------------------------
    // Getters and Setters.

    b2Body* GetBody() { return _body; }

    void SetLinearVelocity(b2Vec2 newVelocity) { _body->SetLinearVelocity(newVelocity); }
    void SetLinearDamping(float newDamping) { _body->SetLinearDamping(newDamping); }
    int GetBombNbr() { return _bombNbr; }
    void SetBombNumber(int nbr) { _bombNbr += nbr; }
    void SetNewLife(int nbr) { _maxLife += nbr; _currentLife += nbr; }
    bool CanMove() { return _canMove; }
    void SetToNotMove() { _canMove = false; }
    bool IsDead() { return _isDead; }
    void SetToDead() { _isDead = true; }

    int GetCurrentLife() { return _currentLife; }
    int GetMaxLife() { return _maxLife; }
    int GetMaxLives() { return _maxLives; }
    bool CanShoot() { return _canShoot; }
    void SetCanShootToFalse() { _canShoot = false; }

    void SetCurrentLifeToMax() { _currentLife = _maxLife; }
    void TakeDamage(int damage) { _currentLife -= damage; }

    // -------------------------------------------------------------------------------------------
};