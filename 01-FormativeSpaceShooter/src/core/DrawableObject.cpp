#include "core/DrawableObject.h"

#include "core/Properties.h"

void DrawableObject::InitSprite(std::string path)
{
    if (!_texture.loadFromFile(path))
    {
        return;
    }

    _texture.setSmooth(true);

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);
}

sf::RectangleShape DrawableObject::CreateAShape(sf::Vector2f size, float x, float y, sf::Color fillColor)
{
    sf::RectangleShape shape;

    shape.setSize(size);
    shape.setPosition(x, y);

    shape.setFillColor(fillColor);

    return shape;
}

void DrawableObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(_sprite, states);
}
