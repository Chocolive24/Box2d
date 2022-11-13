
#include "screenInterface/Score.h"

#include "core/Properties.h"

Score::Score()
{
	if (!_font.loadFromFile("data/font/kenvector_future.ttf"))
	{
		return;
	}

	_scoreText = Init("Score : " + std::to_string(_scorePoints), 
		Properties::WINDOW_WIDTH * 0.885f, Properties::WINDOW_HEIGHT * 0.02f);
}

sf::Text Score::Init(std::string string, float x, float y)
{
	sf::Text textModel;

	textModel.setFont(_font);

	textModel.setString(string);
	textModel.setCharacterSize(30);
	textModel.setFillColor(Properties::GREEN);
	textModel.setStyle(sf::Text::Bold);

	textModel.setOrigin(textModel.getLocalBounds().width / 2.0f, textModel.getLocalBounds().height / 2.0f);
	textModel.setPosition(x, y);

	return textModel;
}

void Score::Update()
{
	_scoreText.setString("Score : " + std::to_string(_scorePoints));
	_scoreText.setOrigin(_scoreText.getLocalBounds().width / 2.0f, _scoreText.getLocalBounds().height / 2.0f);
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_scoreText, states);
}
