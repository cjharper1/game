#include "EventHandler/EventHandler.h"
#include "Physics/PhysicsEngine.h"
#include <SFML/Graphics.hpp>
#include <thread>

// FORWARD DECLARATIONS.
void test(PhysicsEngine& physics_engine, sf::Shape& shape);

int main()
{
	// CREATE THE MAIN WINDOW.
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Secret of Adventure of Monkey Saves Science III");
	
	// CREATE A GREEN CIRCLE.
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// INITIALIZE THE EVENT HANDLER.
	EventHandler event_handler;
	
	// HANDLE THE PHYSICS.
	PhysicsEngine physics_engine(
		event_handler,
		window);
	std::thread physics_thread(
		test,
		physics_engine,
		shape);

	// EXECUTE GAME AS LONG AS WINDOW IS OPEN.
	while (window.isOpen())
	{
		// CLEAR THE WINDOW BUFFER.
		window.clear();

		// DRAW THE CIRCLE TO THE SCREEN BUFFER.
		window.draw(shape);

		// DISPLAY THE NEW SCREEN.
		window.display();
	}

	return 0;
}

void test(PhysicsEngine& physics_engine, sf::Shape& shape)
{
	physics_engine.Process(shape);
}