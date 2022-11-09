#include "Player.h"

#include <iostream>

#include "Properties.h"
#include "Utility.h"

Player::Player(b2World& world) 
{
    Init(world);
}

void Player::Init(b2World& world)
{
    // ---------------------------------------------------------------------------------------------------------
    // Shape Init.

    createSprite("data/sprites/PNG/playerShip1_red.png");

    // ---------------------------------------------------------------------------------------------------------
    // Body, Hit box, and Fixture Init.

    _startPosition = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH / 2.0f,
														  Properties::WINDOW_HEIGHT / 2.0f));
    createBody(world, _startPosition);
    _hitBox = createPolygonHitBox();
    _userData->SetType(UserDataType::PLAYER);
    createFixture(_hitBox, (int)_userData->GetType());
    

    // ---------------------------------------------------------------------------------------------------------
    // Life bar and Lives Init.

    InitLifeBar();
    InitLives();

    /*if (!_shipTexture.loadFromFile("data/sprites/PNG/playerShip1_red.png"))
    {
        return;
    }

    _shipTexture.setSmooth(true);

    _shipSprite.setTexture(_shipTexture);
    _shipSprite.setOrigin(_shipSprite.getGlobalBounds().width / 2.0f, _shipSprite.getGlobalBounds().height / 2.0f);*/

    /*sf::Color damaged(_shipSprite.getColor().r, _shipSprite.getColor().g,
        _shipSprite.getColor().b, _shipSprite.getColor().a - 200);

    _shipSprite.setColor(damaged);*/

    //_shipSprite.setScale(0.8f, 0.8f);

    if (!_fireTexture.loadFromFile("data/sprites/PNG/Effects/fire07.png"))
    {
        return;
    }

    _fireTexture.setSmooth(true);

    _fireSprite.setTexture(_fireTexture);
    _fireSprite.setOrigin(_fireSprite.getGlobalBounds().width / 2.0f, _fireSprite.getGlobalBounds().height / 2.0f);

    // ---------------------------------------------------------------------------------------------------------
   // Body Def Init.

    //_bodyDef.fixedRotation = true;
    //_bodyDef.type = b2_dynamicBody;
    ////_bodyDef.linearDamping = 1.5f;
    //b2Vec2 windowSize(Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_WIDTH,
    //    Properties::WINDOW_HEIGHT)));
    //_bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);

    //_body = world.CreateBody(&_bodyDef);

    //// ---------------------------------------------------------------------------------------------------------
    //// Physical shape Init.

    //float spriteWidth  = Utility::PixelToMeters(_shipSprite.getGlobalBounds().width);
    //float spriteHeight = Utility::PixelToMeters(_shipSprite.getGlobalBounds().height);

    //_hitBox.SetAsBox(spriteWidth / 2.0f, spriteHeight / 2.0f);

    //// ---------------------------------------------------------------------------------------------------------
    //// Fixture Init.

    //_playerFixtureDef.shape = &_hitBox;
    //_playerFixtureDef.density = 2.0f;
    //_playerFixtureDef.friction = 0.0f;
    ////FixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    //_body->CreateFixture(&_playerFixtureDef);

    //_body->SetUserData(this);
}

void Player::InitLifeBar()
{
    _currentLife = _maxLife;

    _currentLifeBar.setFillColor(Properties::GREEN);

    _currentLifeBar.setSize(sf::Vector2f(2 * _currentLife, 20));
    _currentLifeBar.setPosition(12, 15);

    _damagedLifeBar.setFillColor(sf::Color::Red);
    _damagedLifeBar.setOutlineThickness(2.0f);
    _damagedLifeBar.setOutlineColor(sf::Color::Black);

    _damagedLifeBar.setSize(sf::Vector2f(2 * _maxLife, 20));
    _damagedLifeBar.setPosition(12, 15);
}

void Player::InitLives()
{
    if (!_livesTexture.loadFromFile("data/sprites/PNG/UI/playerLife1_red.png"))
    {
        return;
    }

    _livesTexture.setSmooth(true);

    for (int width = 0; width < _maxLives; width++)
    {
        sf::Sprite sprite;
        sprite.setTexture(_livesTexture);
        sprite.setPosition(_currentLifeBar.getPosition().x + sprite.getLocalBounds().width * width * 1.2,
						   _currentLifeBar.getPosition().y + 2 * _currentLifeBar.getLocalBounds().height);
        _lives.emplace_back(sprite);
    }
}

void Player::Move(b2Vec2 force)
{
    _body->ApplyForceToCenter((force), true);
}

void Player::Rotate(float omega)
{
    _body->ApplyTorque(omega, true);
    _body->SetTransform(_body->GetPosition(), omega);
    
    _sprite.rotate(_body->GetAngle());
}

void Player::AddLaser(b2World& world)
{
    
}

void Player::Shoot(b2World& world)
{
    Laser* laser = new Laser;
    b2Vec2 startPos(_body->GetPosition().x, _body->GetPosition().y + 1.0f);
    laser->Init(world, startPos);
    _lasers.emplace_back(laser);

    laser->PlaySound();

	laser->Move(b2Vec2(0, 50));
}

void Player::ThrowBomb(b2World& world)
{
    if (_bombNbr > 0)
    {
        Bomb* bomb = new Bomb;
        b2Vec2 startPos(_body->GetPosition().x, (_body->GetPosition().y + 1.0f));
        bomb->Init(world, startPos);
        _bombs.emplace_back(bomb);

        bomb->PlaySound();

        bomb->Move(b2Vec2(0, 50));

        _bombNbr -= 1;
    }
}

void Player::update()
{
    // -------------------------------------------------------------------------------------------------------------
    // Update the ship.

    GameObject::update();

    // Get the position of the body
    //b2Vec2 bodyPos = _body->GetPosition();

    //// Translate meters to pixels
    //sf::Vector2f graphicPosition(Utility::MetersToPixels(b2Vec2(bodyPos)));

    //// Set the position of the Graphic object
    //_sprite.setPosition(graphicPosition);

    /*_fireSprite.setPosition(graphicPosition.x, 
        graphicPosition.y + _fireSprite.getLocalBounds().height + _shipSprite.getLocalBounds().height / 2.0f);*/

	// -------------------------------------------------------------------------------------------------------------
	// Update the player's data.

    _currentLifeBar.setSize(sf::Vector2f(2 * _currentLife, 20));

    // -------------------------------------------------------------------------------------------------------------
    // Update the player's attacks.

    for (auto& laser : _lasers)
    {
        laser->update();
    }

    for (auto& bomb : _bombs)
    {
        bomb->update();
    }

    // -------------------------------------------------------------------------------------------------------------
    // Tests.

   /* std::cout << _hitBox.m_vertices->x << " " << _hitBox.m_vertices->y << std::endl;
    std::cout << _shipSprite.getGlobalBounds().width << " " << _shipSprite.getGlobalBounds().height << std::endl;*/

    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
    //std::cout << _body->GetAngularVelocity() << std::endl;

    /*std::cout << "body position [" << _body->GetPosition().x << ":" << _body->GetPosition().y
        << "]|shape position [" << _shipSprite.getPosition().x << ":" << _shipSprite.getPosition().y << "]" << std::endl;*/
    //std::cout << _body->GetLinearVelocity().x << " " << _body->GetLinearVelocity().y << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    /*states.transform *= getTransform();

    target.draw(_sprite, states);*/
    //target.draw(_fireSprite, states);

    GameObject::draw(target, states);

    for (auto& laser : _lasers)
    {
        target.draw(*laser);
    }
    for (auto& bomb : _bombs)
    {
        target.draw(*bomb);
    }

    target.draw(_damagedLifeBar);
    target.draw(_currentLifeBar, states);
    for (auto& lives : _lives)
    {
        target.draw(lives);
    }
    
}
