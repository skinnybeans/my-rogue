#include "PCH.hpp"
#include "Slime.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

// Default constructor.
Slime::Slime()
{
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/slime/spr_slime_idle_left.png");

	// Set initial sprite.
	GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), false, 8, 12);
    
    // Randomise the colour used for the slime
    COLOR color = static_cast<COLOR>(rand() % static_cast<int>(COLOR::COUNT));
    sf::Color spriteColor = sf::Color::Black;
    switch (color) {
        case COLOR::BLACK:
            spriteColor = sf::Color::Black;
            break;
        case COLOR::BLUE:
            spriteColor = sf::Color::Blue;
            break;
        case COLOR::RED:
            spriteColor = sf::Color::Red;
            break;
        case COLOR::GREEN:
            spriteColor = sf::Color::Green;
            break;
        case COLOR::WHITE:
            spriteColor = sf::Color::White;
            break;
        case COLOR::YELLOW:
            spriteColor = sf::Color::Yellow;
            break;
        case COLOR::MAGENTA:
            spriteColor = sf::Color::Magenta;
            break;
        case COLOR::CYAN:
            spriteColor = sf::Color::Cyan;
            break;
        case COLOR::TRANSPARENT:
            // random color!
            spriteColor = sf::Color(std::rand()%256,std::rand()%256,std::rand()%256,std::rand()%156+100);
        case COLOR::COUNT:
            // TODO error...
            break;
    }
    
    GetComponent<SpriteComponent>()->GetSprite().setColor(spriteColor);
    
    // Randomise the size of the slime
    float scale = ((std::rand() % 5) + 5) / 10.f;
    GetComponent<SpriteComponent>()->GetSprite().setScale(sf::Vector2f(scale, scale));
}
