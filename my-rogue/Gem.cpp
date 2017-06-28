#include "PCH.hpp"
#include "Gem.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

// Default Constructor.
Gem::Gem()
{
	// Set the sprite.
    //GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/loot/gem/spr_pickup_gem.png")), false, 8, 12);

    GetComponent<SpriteComponent>()->SetAnimatedTexture(TextureManager::GetAnimatedTexture(TextureManager::AddAnimatedTexture(resourcePath() + "/resources/loot/gem/spr_pickup_gem.png", 8)));
    
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);

	// Set the value of the gem.
    m_scoreValue = std::rand() % 100;

	// Set the item type.
	m_type = ITEM::GEM;
}

// Gets the amount of score this pickup gives.
int Gem::GetScoreValue() const
{
	return m_scoreValue;
}
