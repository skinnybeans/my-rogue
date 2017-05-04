#include "PCH.hpp"
#include "Game.hpp"

#include <iostream>
// Entry point of the application.
int main()
{
    // Set a random seed.
    std:: srand(static_cast<unsigned int>(time(nullptr)));
    
	// Create the main game object.
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Slaughter o Smogs", sf::Style::Fullscreen);
	Game game(&window);

	// Initialize and run the game object.
	game.Initialize();
	game.Run();

	// Exit the application.
	return 0;
}
