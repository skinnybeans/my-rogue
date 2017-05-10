#include "PCH.hpp"
#include "Humanoid.hpp"
#include "ResourcePath.hpp"

// Default constructor.
Humanoid::Humanoid()
{
    // Randomise the type of humanoid enemy
    ENEMY_HUMANOIDS humanoidType = static_cast<ENEMY_HUMANOIDS>(rand() % static_cast<int>(ENEMY_HUMANOIDS::COUNT));
    
    std::string enemyName = "";
    
    switch (humanoidType)
    {
        case ENEMY_HUMANOIDS::SKELETON:
            enemyName = "skeleton";
            break;
        case ENEMY_HUMANOIDS::GOBLIN:
            enemyName = "goblin";
            break;
        case ENEMY_HUMANOIDS::COUNT:
            // error!
            break;
    }
    
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
}
