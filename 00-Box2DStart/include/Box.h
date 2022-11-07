#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <SFML/Graphics.hpp>

#include "debugDraw.h"

class Box : public b2Draw
{
    // Defining the shape
    sf::RectangleShape _box;


    // Defing the _box 2D elements
    b2BodyDef _bodyDef;

    b2Body* _body = nullptr;

    // Shape of the physical (A _box)
    b2PolygonShape physicalBox;


    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;

	sf::RenderWindow* m_window;

public:
    Box(b2World& world, sf::RenderWindow& window);

	b2Body* GetBody() { return _body; }

	void SetPosition(sf::Vector2f newPos) { return _box.setPosition(newPos); }

	/// Convert Box2D's OpenGL style color definition[0-1] to SFML's color definition[0-255], with optional alpha byte[Default - opaque]
	static sf::Color GLColorToSFML(const b2Color& color, sf::Uint8 alpha = 255)
	{
		return sf::Color(static_cast<sf::Uint8>(color.r * 255), static_cast<sf::Uint8>(color.g * 255), static_cast<sf::Uint8>(color.b * 255), alpha);
	}

	/// Convert Box2D's vector to SFML vector [Default - scales the vector up by SCALE constants amount]
	static sf::Vector2f B2VecToSFVec(const b2Vec2& vector, bool scaleToPixels = true)
	{
		return sf::Vector2f(vector.x * (scaleToPixels ? sfdd::SCALE : 1.f), vector.y * (scaleToPixels ? sfdd::SCALE : 1.f));
	}

	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);

	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);

	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	/// Draw a transform. Choose your own length scale.
	void DrawTransform(const b2Transform& xf);

	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
};
