#include "screenInterface/Button.h"

#include <iostream>

#include "core/Properties.h"

void Button::SetPosition(float x, float y)
{
	_shape.setPosition(x, y);
	_buttonText.SetTextPosition(_shape.getPosition().x, 
		_shape.getPosition().y - _buttonText.GetLocalBounds().height / 2.0f);
	_sprite.setPosition(_shape.getPosition().x, _shape.getPosition().y + _shape.getLocalBounds().height / 1.75f);
}

void Button::Init(float x, float y, sf::Vector2f size, std::string string, int charSize, std::string path)
{
	InitShape(x, y, size);

	InitText(string, charSize);

	InitKeySprite(path);
}

void Button::InitShape(float x, float y, sf::Vector2f size)
{
	_shape.setSize(size);
	_shape.setOrigin(_shape.getLocalBounds().width / 2.0f, _shape.getLocalBounds().height / 2.0f);
	_shape.setPosition(x, y);
	//_shape.setFillColor(sf::Color(50, 50, 50));
	_shape.setFillColor(Properties::DARK_GREEN);
	_shape.setOutlineThickness(3.0f);
	_shape.setOutlineColor(sf::Color::Black);
}

void Button::InitText(std::string string, int charSize)
{
	_buttonText.Init(string, _shape.getPosition().x, _shape.getPosition().y,
		charSize, Properties::GREEN);
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
	target.draw(_buttonText,   states);
	target.draw(_sprite, states);
}