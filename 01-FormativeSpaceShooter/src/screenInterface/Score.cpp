
#include "screenInterface/Score.h"

#include "core/Properties.h"

Score::Score()
{
	GameText::Init("Score : " + std::to_string(_scorePoints), 
		Properties::WINDOW_WIDTH * 0.885f, Properties::WINDOW_HEIGHT * 0.02f, 30, Properties::GREEN);
}

void Score::Update()
{
	_text.setString("Score : " + std::to_string(_scorePoints));
	_text.setOrigin(_text.getLocalBounds().width / 2.0f, _text.getLocalBounds().height / 2.0f);
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameText::draw(target, states);
}
