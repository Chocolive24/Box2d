#include "screenInterface/Button.h"

#include <iostream>

#include "core/Properties.h"

void Button::Init(float x, float y, std::string string, std::string path)
{
	InitShape(x, y);

	InitText(string);

	InitKeySprite(path);
}

void Button::InitShape(float x, float y)
{
	_shape.setSize(sf::Vector2f(300, 100));
	_shape.setOrigin(_shape.getLocalBounds().width / 2.0f, _shape.getLocalBounds().height / 2.0f);
	_shape.setPosition(x, y);
	//_shape.setFillColor(sf::Color(50, 50, 50));
	_shape.setFillColor(Properties::DARK_GREEN);
	_shape.setOutlineThickness(3.0f);
	_shape.setOutlineColor(sf::Color::Black);
}

void Button::InitText(std::string string)
{
	if (!_font.loadFromFile("data/font/kenvector_future.ttf"))
	{
		return;
	}

	_text.setFont(_font);

	_text.setString(string);
	_text.setCharacterSize(60);
	_text.setFillColor(Properties::GREEN);
	_text.setStyle(sf::Text::Bold);

	_text.setOrigin(_text.getLocalBounds().width / 2.0f, _text.getLocalBounds().height / 2.0f);
	_text.setPosition(_shape.getPosition().x, _shape.getPosition().y - _text.getLocalBounds().height / 2.0f);
}

void Button::InitKeySprite(std::string path)
{
	if (!_texture.loadFromFile(path))
	{
		return;
	}

	_texture.setSmooth(true);

	_sprite.setTexture(_texture);
	_sprite.setScale(2, 2);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2.0f, 
					  _sprite.getLocalBounds().height / 2.0f );

	_sprite.setColor(Properties::GREEN);

	_sprite.setPosition(_shape.getPosition().x, _shape.getPosition().y + _shape.getLocalBounds().height / 1.75f);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape,  states);
	target.draw(_text,   states);
	target.draw(_sprite, states);
}