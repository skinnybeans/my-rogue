#include "PCH.hpp"
#include "Potion.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

// Default constructor.
Potion::Potion() :
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0),
m_accuracy(0)
{
    // texture file path
    std::string textureName;
    
    // set the potion type
    m_potionType = static_cast<POTION>(rand() % static_cast<int>(POTION::COUNT));;
    int potionBoost = std::rand() % 11 + 5;
    
    // set potion texture and stat boost
    switch(m_potionType)
    {
        case POTION::ATTACK:
            m_attack = potionBoost;
            textureName = "spr_potion_attack.png";
            break;
        case POTION::DEFENSE:
            m_defense = potionBoost;
            textureName = "spr_potion_defense.png";
            break;
        case POTION::DEXTERITY:
            m_dexterity = potionBoost;
            textureName = "spr_potion_dexterity.png";
            break;
        case POTION::STRENGTH:
            m_strength = potionBoost;
            textureName = "spr_potion_strength.png";
            break;
        case POTION::STAMINA:
            m_stamina = potionBoost;
            textureName = "spr_potion_stamina.png";
            break;
        case POTION::ACCURACY:
            m_accuracy = potionBoost;
            textureName = "spr_potion_accuracy.png";
            break;
        case POTION::COUNT:
            // error!
            break;
    }
    
    
	// Load and set sprite.
	GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/loot/potions/" + textureName)), false, 8, 12);

	// Set the item type.
	m_type = ITEM::POTION;
}

// Gets the potion type
POTION Potion::GetPotionType() const
{
    return m_potionType;
}

// Gets the attack value of the potion.
int Potion::GetAttack() const
{
	return m_attack;
}

// Gets the defense value of the potion.
int Potion::GetDefense() const
{
	return m_defense;
}

// Gets the strength value of the potion.
int Potion::GetStrength() const
{
	return m_strength;
}

// Gets the dexterity value of the potion.
int Potion::GetDexterity() const
{
	return m_dexterity;
}

// Gets the stamina value of the potion.
int Potion::GetStamina() const
{
	return m_stamina;
}

// Gets the accuracy value of the potion.
int Potion::GetAccuracy() const
{
    return m_accuracy;
}
