#include <iostream>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <SFML/Graphics.hpp>

int main()
{
    const float pixelMetersRatio = 100.0f;

    sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    
    // Creating the world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // Defining the shape
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(100.0f, 100.0f));
    box.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize(window.getSize().x / pixelMetersRatio, window.getSize().y / pixelMetersRatio);
    bodyDef.position.Set(0, 0);
    b2Body* body = world.CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2PolygonShape physicalBox;
    physicalBox.SetAsBox(box.getSize().x / pixelMetersRatio, box.getSize().y / pixelMetersRatio);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &physicalBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);


    /*std::cout << "Box graphique : " << box.getSize().x << ":" << box.getSize().y << std::endl;
    std::cout << "Box physique : " << physicalBox.m_vertices->x << ": "
        << physicalBox.m_vertices->y << std::endl;
    std::cout << windowSize.x << ":" << windowSize.y << std::endl;
    std::cout << body->GetPosition().x << ":" << body->GetPosition().y << std::endl;*/

    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;

        while (window.pollEvent(event))
        {

            switch (event.type)
            {

                // évènement "fermeture demandée" : on ferme la fenêtre
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:

                // Put in mouse position
                body->SetTransform(b2Vec2 (event.mouseButton.x / pixelMetersRatio,
                    -1.0f * event.mouseButton.y / pixelMetersRatio), body->GetAngle());
                // Reset the velocity (Speed)
                body->SetLinearVelocity(b2Vec2_zero);

            	box.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
				case sf::Keyboard::Space:

                std::cout << "OUI";
                    body->ApplyForceToCenter(b2Vec2(10, 6), true);
                    box.setPosition(body->GetPosition().x * pixelMetersRatio, 
									body->GetPosition().y * -pixelMetersRatio);
                    break;
                }
            default:
                break;
            }

        }

        // Updating the world with a delay
        float timeStep = 1.0f / 30.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        world.Step(timeStep, velocityIterations, positionIterations);


        std::cout << "body position [" << body->GetPosition().x << ":" << body->GetPosition().y
            << "]|shape position [" << box.getPosition().x << ":" << box.getPosition().y << "]" << std::endl;

        /*
        if (body->GetPosition().y < -(window.getSize().y / pixelMetersRatio))
        {
            std::cout << "LETSGO  LA PHYSIQUE" << std::endl;
        }

        if (box.getPosition().y > window.getSize().y)
        {
            std::cout << "LETSGO  LES GRAPH" << std::endl;
        }*/

        // Get the position of the body
        b2Vec2 bodyPos = body->GetPosition();
        // Translate meters to pixels
        sf::Vector2f graphicPosition(bodyPos.x * pixelMetersRatio, - bodyPos.y * pixelMetersRatio);
        // Set the position of the Graphic object
        box.setPosition(graphicPosition);

        // Graphical Region
        window.clear(sf::Color::Black);

        //window.draw(something to draw);
        ////window.draw(box);

        // Window Display
        window.display();

        
    }
}