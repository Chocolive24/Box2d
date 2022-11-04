#include <iostream>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <SFML/Graphics.hpp>

#include "Game.h"

// TODO player::Stop()
// TODO body->SetLinearVelocity(b2Vec2(0, 0))
// TODO body->SetlinearDamping(0.9)

int main()
{
    const float pixelMetersRatio = 100.0f;

    
    Game game;

    game.Init();

    return game.GameLoop();
    
    

    


    /*std::cout << "Box graphique : " << box.getSize().x << ":" << box.getSize().y << std::endl;
    std::cout << "Box physique : " << physicalBox.m_vertices->x << ": "
        << physicalBox.m_vertices->y << std::endl;
    std::cout << windowSize.x << ":" << windowSize.y << std::endl;
    std::cout << body->GetPosition().x << ":" << body->GetPosition().y << std::endl;*/

    
}