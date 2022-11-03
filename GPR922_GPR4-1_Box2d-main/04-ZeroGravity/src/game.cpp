#include "game.h"

const float Game::pixelsMetersRatio = 100.0f;

Game::Game() :
	theBall(*this, this->window_),
	gravity_(0.0f, 0.0f),
	world_(gravity_),
	contactListener_(*this)
{

}

void Game::init() {

	world_.SetContactListener(&contactListener_);

	window_.create(sf::VideoMode(1280, 720), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60.0f);

	// Init all elements
	theBall.init();

	// Add a bouncer
	// TOP LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			this->window_,
			sf::Vector2f(0.5f * window_.getSize().x, 0.0f),
			sf::Vector2f(window_.getSize().x, 10.0f)
		)
	);
	// BOTTOM LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			this->window_,
			sf::Vector2f(0.5f * window_.getSize().x, window_.getSize().y),
			sf::Vector2f(window_.getSize().x, 10.0f)
		)
	);
	// LEFT LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			this->window_,
			sf::Vector2f(0.0f, 0.5f * window_.getSize().y),
			sf::Vector2f(10.0F, window_.getSize().y)
		)
	);
	// RIGHT LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			this->window_,
			sf::Vector2f(window_.getSize().x, 0.5f * window_.getSize().y),
			sf::Vector2f(10.0f, window_.getSize().y)
		)
	);

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
				if (event.mouseButton.button == sf::Mouse::Right) {
					//// mouse Released position detect
					mousePressedPos_sensor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					// mouse Released position detect
					mousePressedPos_ball = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					//// mouse Released position detect
					mouseReleasedPos_sensor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

					sensors.push_back(
						mySensor(
							*this,
							this->window_,
							//sf::Vector2f(event.mouseButton.x, event.mouseButton.y),
							//50.0f
							Vector2f(
								0.5f * mouseReleasedPos_sensor.x + 0.5f * mousePressedPos_sensor.x,
								0.5f * mouseReleasedPos_sensor.y + 0.5f * mousePressedPos_sensor.y),
							0.5f * vecDistance(mousePressedPos_sensor, mouseReleasedPos_sensor)
						)
					);
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouseReleasedPos_ball = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					sf::Vector2f velocity(mouseReleasedPos_ball.x - mousePressedPos_ball.x, mouseReleasedPos_ball.y - mousePressedPos_ball.y);

					theBall.setPixelsPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), velocity);
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
		for (auto b = windowLimits.begin(); b != windowLimits.end(); b++) {
			b->update();
		}
		for (auto s = sensors.begin(); s != sensors.end(); s++) {
			s->update();
		}
#pragma endregion


#pragma region Graphics process
		// Clear all background
		window_.clear();
		// Render All elements
		theBall.render();
		for (auto b = windowLimits.begin(); b != windowLimits.end(); b++) {
			b->render();
		}
		for (auto s = sensors.begin(); s != sensors.end(); s++) {
			s->render();
		}
		// Display all elements
		window_.display();
#pragma endregion

	}
}

b2Vec2 Game::pixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, 1.0f * pixels.y / pixelsMetersRatio);
}

b2Vec2 Game::pixelsToMeters(sf::Vector2u pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, 1.0f * pixels.y / pixelsMetersRatio);
}

float Game::pixelsToMeters(float pixels)
{
	return pixels / pixelsMetersRatio;
}

sf::Vector2f Game::metersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * pixelsMetersRatio, 1.0f * meters.y * pixelsMetersRatio);
}

void Game::clearBouncers()
{

	for (auto myBouncer = sensors.begin(); myBouncer != sensors.end(); myBouncer++)
	{
		// First remove bodies from the physical world
		world_.DestroyBody(myBouncer->getBody());
		// Notice that the iterator is decremented after it is passed
		// to `erase()` but before `erase()` is executed
		//bouncers.erase(myBouncer--);
	}

	sensors.clear();

}

//void Game::BeginContact(UserDataType userData, UserDataType userData1)
//{
//	if (userData == UserDataType::BOUNCER)
//	{
//		// Play some sound
//	}
//}
//
//void Game::EndContact(UserDataType userData, UserDataType userData1)
//{
//	if (userData == UserDataType::BOUNCER)
//	{
//		// Nothing less
//	}
//}
