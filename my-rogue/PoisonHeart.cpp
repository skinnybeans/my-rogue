//
//  PoisonHeart.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 8/5/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//
#include "PCH.hpp"
#include "PoisonHeart.hpp"
#include "ResourcePath.hpp"

// Default constructor.
PoisonHeart::PoisonHeart()
{
    // Set item sprite.
    SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/loot/poison_heart/spr_pickup_poison_heart.png")), false, 8, 12);
    
    // Set health value.
    m_health = -15;
    
    // Set item type.
    m_type = ITEM::POISON_HEART;
}

// Returns the amount of health that the heart gives.
int PoisonHeart::GetHealth() const
{
    return m_health;
}
