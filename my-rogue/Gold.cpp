#include "PCH.hpp"
#include "Gold.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"


static const int GOLD_SMALL = 9;
static const int GOLD_LARGE = 15;

// Default constructor.
Gold::Gold()
{
	// Set gold value.
    this->m_goldValue = std::rand() % 21 + 5;
    
    
	// Set the sprite.
	int textureID;
    
    if(this->m_goldValue <= GOLD_SMALL)
    {
        textureID = TextureManager::AddTexture(resourcePath() + "/resources/loot/gold/spr_pickup_gold_small.png");
    }
    else if(this->m_goldValue < GOLD_LARGE)
    {
        textureID = TextureManager::AddTexture(resourcePath() + "/resources/loot/gold/spr_pickup_gold_medium.png");
    }
    else
    {
        textureID = TextureManager::AddTexture(resourcePath() + "/resources/loot/gold/spr_pickup_gold_large.png");
    }

	GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

	// Set the item type.
	m_type = ITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return m_goldValue;
}
