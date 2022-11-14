#include "screenInterface/GameText.h"

#include "core/Properties.h"

void GameText::Init (std::string string, float x, float y, int charSize, sf::Color color)
{
	if (!_font.loadFromFile("data/font/kenvector_future.ttf"))
	{
		return;
	}

	_text.setFont(_font);

	_text.setString(string);
	_text.setCharacterSize(charSize);
	_text.setFillColor(color);
	_text.setStyle(sf::Text::Bold);

	_text.setOrigin(_text.getLocalBounds().width / 2.0f, _text.getLocalBounds().height / 2.0f);
	_text.setPosition(x, y - _text.getLocalBounds().height / 2.0f);
}

void GameText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_text);
}
