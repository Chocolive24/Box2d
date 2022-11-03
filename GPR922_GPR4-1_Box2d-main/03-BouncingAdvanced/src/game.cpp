#include "game.h"

const float Game::pixelsMetersRatio = 100.0f;

Game::Game() :
	theBall(*this, this->window_),
	gravity_(0, -9.81f),
	world_(gravity_)
{

}

void Game::init() {

	window_.create(sf::VideoMode(1280, 720), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60.0f);

	// Init all elements
	theBall.init();

}

void Game::loop()
{

	while (window_.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (window_.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				window_.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = window_.getView();
				view.setSize(event.size.width, event.size.height);
				window_.setView(view);
			}

			// Mouse events ---------------------------------------------------------------------------------
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					// mouse Released position detect
					mousePressedPos_bouncer = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					// mouse Released position detect
					mousePressedPos_ball = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					mouseReleasedPos_ball = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					sf::Vector2f velocity(mouseReleasedPos_ball.x - mousePressedPos_ball.x, mouseReleasedPos_ball.y - mousePressedPos_ball.y);

					theBall.setPixelsPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), velocity);
				}

				if (event.mouseButton.button == sf::Mouse::Left) {
					// mouse Released position detect
					mouseReleasedPos_bouncer = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

					// Add a bouncer
					Bouncer newBouncer(*this, this->window_, mousePressedPos_bouncer, mouseReleasedPos_bouncer);
					bouncers.push_back(newBouncer);
				}
			}
			// Keyboard events
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					clearBouncers();
				}
			}
		}
#pragma endregion


#pragma region Physical process
		// Updating the world with a delay
		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		world_.Step(timeStep, velocityIterations, positionIterations);

		// Update the elements
		theBall.update();
		for (auto b = bouncers.begin(); b != bouncers.end(); b++) {
			b->update();
		}

#pragma endregion


#pragma region Graphics process
		// Clear all background
		window_.clear();
		// Render All elements
		theBall.render();
		for (auto b = bouncers.begin(); b != bouncers.end(); b++) {
			b->render();
		}
		// Display all elements
		window_.display();
#pragma endregion

	}
}

b2Vec2 Game::pixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

b2Vec2 Game::pixelsToMeters(sf::Vector2u pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

float Game::pixelsToMeters(float pixels)
{
	return pixels / pixelsMetersRatio;
}

sf::Vector2f Game::metersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * pixelsMetersRatio, -1.0f * meters.y * pixelsMetersRatio);
}

void Game::clearBouncers()
{

	for (auto myBouncer = bouncers.begin(); myBouncer != bouncers.end(); myBouncer++)
	{
		// First remove bodies from the physical world
		world_.DestroyBody(myBouncer->getBody());
		// Notice that the iterator is decremented after it is passed
		// to `erase()` but before `erase()` is executed
		//bouncers.erase(myBouncer--);
	}

	bouncers.clear();

}
