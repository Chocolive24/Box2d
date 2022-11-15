#include "screenInterface/Edge.h"

#include <iostream>
#include <box2d/b2_edge_shape.h>

#include "Game.h"
#include "core/Utility.h"

Edge::Edge(Game& game, sf::Vector2f v1, sf::Vector2f v2) : _game(game)
{
    b2BodyDef bodyDef;

    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    //_bodyDef.linearDamping = 1.5f;

    _body = _game.GetWorld().CreateBody(&bodyDef);

    b2EdgeShape hitBox;
    hitBox.SetTwoSided(Utility::PixelsToMeters(v1), Utility::PixelsToMeters(v2));

    std::cout << hitBox.m_vertex1.x << " " << hitBox.m_vertex1.y << std::endl;
    std::cout << hitBox.m_vertex2.x << " " << hitBox.m_vertex2.y << std::endl;

    _fixtureDef.shape = &hitBox;
    _fixtureDef.density = 2.0f;
    _fixtureDef.friction = 0.0f;

    _userData = new UserData(*this);
    _userData->SetType(UserDataType::EDGE);

    if (!_addedToGroupIndex)
    {
        _fixtureDef.filter.categoryBits = (uint16)UserDataType::EDGE;
        _fixtureDef.filter.maskBits = (uint16)UserDataType::PLAYER;
        _addedToGroupIndex = true;
    }

    _fixtureDef.userData.pointer = reinterpret_cast<std::uintptr_t>(_userData);
    _body->CreateFixture(&_fixtureDef);
}
