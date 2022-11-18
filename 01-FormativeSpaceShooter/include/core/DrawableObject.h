#pragma once
#include <SFML/Graphics.hpp>

class DrawableObject : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;

public:
	void InitSprite(std::string path);
	sf::RectangleShape CreateAShape(sf::Vector2f size, float x, float y, sf::Color fillColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite& GetSprite() { return _sprite; }
};