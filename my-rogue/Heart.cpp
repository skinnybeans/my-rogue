#include "PCH.hpp"
#include "Heart.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

// Default constructor.
Heart::Heart()
{
	// Set item sprite.
	GetComponent<SpriteComponent>()->SetAnimatedTexture(TextureManager::GetAnimatedTexture(TextureManager::AddAnimatedTexture(resourcePath() + "resources/loot/heart/spr_pickup_heart.png", 8)));
    
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);

	// Set health value.
    m_health = std::rand() % 11 + 10;

	// Set item type.
	m_type = ITEM::HEART;
}

// Returns the amount of health that the heart gives.
int Heart::GetHealth() const
{
	return m_health;
}
