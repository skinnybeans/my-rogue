#include "PCH.hpp"
#include "Slime.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

#include "ServiceLocator.hpp"

// Default constructor.
Slime::Slime()
{
<<<<<<< HEAD
	// Load textures.
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_walk_up.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_walk_down.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_walk_right.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_walk_left.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_idle_up.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_idle_down.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_idle_right.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddAnimatedTexture(resourcePath() + "resources/enemies/slime/spr_slime_idle_left.png", 1);
    
=======
	// Map textures to animation states
    for(int i=0; i<8; i++)
    {
        m_textureIDs[i] = i + static_cast<int>(TEXTURE_ID::ENEMY_SLIME_WALK_UP);
    }
     
>>>>>>> 8c83620 (- Moved enemies over to using texture service)
	// Set initial sprite.
    GetComponent<SpriteComponent>()->SetAnimatedTexture(*ServiceLocator::GetTexture()->GetAnimatedTexture(static_cast<TEXTURE_ID>(m_textureIDs[4])));
    
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);
    
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
            // TODO: error...
            break;
    }
    
    GetComponent<SpriteComponent>()->GetSprite().setColor(spriteColor);
    
    // Randomise the size of the slime
    float scale = ((std::rand() % 5) + 5) / 10.f;
    GetComponent<SpriteComponent>()->GetSprite().setScale(sf::Vector2f(scale, scale));
}
