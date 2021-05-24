#include "PCH.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"
#include "SFMLAudio.hpp"
#include "SFMLTexture.hpp"

#include <iostream>
// Entry point of the application.
int main()
{
    // Set a random seed.
    std:: srand(static_cast<unsigned int>(time(nullptr)));
    
    // Initialise services
    std::shared_ptr<Audio> audio = std::make_shared<SFMLAudio>();
    audio->Initialise();
    ServiceLocator::ProvideAudio(audio);
    
    std::shared_ptr<SFMLTexture> texture = std::make_shared<SFMLTexture>();
    texture->Initialise();
    ServiceLocator::ProvideTexture(texture);
    
	// Create the main game object.
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Slaughter o Smogs", sf::Style::Default);
    Game game(&window);
    
    // Initialize and run the game object
	game.Initialize();
	game.Run();
    game.CleanUp();
    
    texture->CleanUp();
    audio->CleanUp();
    
    // close window after game execution has finished
    window.close();

	// Exit the application.
	return 0;
}
