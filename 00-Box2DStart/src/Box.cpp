#include "Box.h"

Box::Box(b2World& world, sf::RenderWindow& window)
{
    float pixelMetersRatio = 100.0f;

	_box.setSize(sf::Vector2f(100.0f, 100.0f));
	_box.setFillColor(sf::Color::Red);

    _bodyDef.fixedRotation = true;
    _bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize(window.getSize().x / pixelMetersRatio, window.getSize().y / pixelMetersRatio);
    _bodyDef.position.Set(0, 0);
    _body = world.CreateBody(&_bodyDef);

    physicalBox.SetAsBox(_box.getSize().x / pixelMetersRatio, _box.getSize().y / pixelMetersRatio);

    playerFixtureDef.shape = &physicalBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    _body->CreateFixture(&playerFixtureDef);
}

void Box::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	sf::Vector2f center;
	for (int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		sf::Vector2f transformedVec = SFMLDebugDraw::B2VecToSFVec(vertices[i]);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(polygon);
}
void Box::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	for (int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		sf::Vector2f transformedVec = SFMLDebugDraw::B2VecToSFVec(vertices[i]);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(SFMLDebugDraw::GLColorToSFML(color, 60));
	polygon.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(polygon);
}
void Box::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);
	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(SFMLDebugDraw::B2VecToSFVec(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(-1.f);
	circle.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(circle);
}
void Box::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);
	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(SFMLDebugDraw::B2VecToSFVec(center));
	circle.setFillColor(SFMLDebugDraw::GLColorToSFML(color, 60));
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	b2Vec2 endPoint = center + radius * axis;
	sf::Vertex line[2] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(center), SFMLDebugDraw::GLColorToSFML(color)),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(endPoint), SFMLDebugDraw::GLColorToSFML(color)),
	};

	m_window->draw(circle);
	m_window->draw(line, 2, sf::Lines);
}
void Box::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(p1), SFMLDebugDraw::GLColorToSFML(color)),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(p2), SFMLDebugDraw::GLColorToSFML(color))
	};

	m_window->draw(line, 2, sf::Lines);
}
void Box::DrawTransform(const b2Transform& xf)
{
	float lineLength = 0.4;

	/*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
	b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
	sf::Vertex redLine[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xf.p), sf::Color::Red),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xAxis), sf::Color::Red)
	};

	// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
	// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
	/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
	b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
	sf::Vertex greenLine[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xf.p), sf::Color::Green),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(yAxis), sf::Color::Green)
	};

	m_window->draw(redLine, 2, sf::Lines);
	m_window->draw(greenLine, 2, sf::Lines);
}

void Box::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}