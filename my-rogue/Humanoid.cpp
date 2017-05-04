#include "PCH.hpp"
#include "Humanoid.hpp"
#include "ResourcePath.hpp"

// Default constructor.
Humanoid::Humanoid()
{
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/enemies/skeleton/spr_skeleton_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
}
