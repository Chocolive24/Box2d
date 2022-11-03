#include "shape.h"

void Shape::checkTouch(sf::Vector2f mousePosition)
{
    isTouched = m_shape.getGlobalBounds().contains(mousePosition);
}

void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

 Shape::Shape(sf::RenderWindow& window_)
{

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 generator(rd()); // seed the generator

	std::uniform_int_distribution<> rdnRed(0, 255); // define the range
	std::uniform_int_distribution<> rndGreen(0, 255); // define the range
	std::uniform_int_distribution<> rndBlue(0, 255); // define the range
	std::uniform_int_distribution<> rndPositionX(0, window_.getSize().x); // define the range
	std::uniform_int_distribution<> rndPositionY(0, window_.getSize().y); // define the range

	m_shape.setFillColor(sf::Color(rdnRed(generator), rndGreen(generator), rndBlue(generator)));
	
	m_shape.setSize(sf::Vector2f(100, 100));
	m_shape.setOrigin(sf::Vector2f(50, 50));
	m_shape.setPosition(sf::Vector2f(rndPositionX(generator), rndPositionY(generator)));
    m_shape.setScale(0.1, 0.1);

}

void Shape::update()
{
    float scale = sf::Vector2f(m_shape.getScale()).x;

	if(scale < 1.0f)
    {
        scale *= 1.25f;
    }
	m_shape.setScale(sf::Vector2f(scale,scale));

}
