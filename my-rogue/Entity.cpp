#include "PCH.hpp"
#include "Entity.hpp"
#include "SpriteComponent.hpp"
#include "AnimationStateComponent.hpp"
#include "AnimationFramesComponent.hpp"

#include <cmath>

// Default constructor.
Entity::Entity() :
//m_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
m_health(0),
m_maxHealth(0),
m_mana(0),
m_maxMana(0),
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0),
m_speed(0),
m_accuracy(0),
m_velocity({0.f, 0.f})
{
    // Add component to track animation state
    AttachComponent<AnimationStateComponent>();
    
    // Add component to track animation frames
    AttachComponent<AnimationFramesComponent>();
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
    std::shared_ptr<SpriteComponent> spriteComponent = GetComponent<SpriteComponent>();
    std::shared_ptr<AnimationStateComponent> animationState = GetComponent<AnimationStateComponent>();
    std::shared_ptr<AnimationFramesComponent> animationFrames = GetComponent<AnimationFramesComponent>();
    
    animationState->Update(m_velocity);
    
    // Set the sprite texture if the animation state has changed
    if (animationState->HasStateChanged())
    {
        // Reset to the start of the frames for new texture
        animationFrames->Reset();
        
        int textureID = static_cast<int>(animationState->GetState());
        spriteComponent->SetTexture(TextureManager::GetTexture(m_textureIDs[textureID]));
        
        //spriteComponent->GetSprite().setTexture(TextureManager::GetTexture(m_textureIDs[textureID]));
        
        // The sprite should determine its animation state based on the texture size
        // Stopping animation outside of that should be a special case
        // Set animation speed.
        if ((m_velocity.x == 0) && (m_velocity.y == 0))
        {
            spriteComponent->SetAnimated(false);
        }
        else
        {
            spriteComponent->SetAnimated(true);
        }
    }
}

// Gets the entities health.
int Entity::GetHealth() const
{
	return m_health;
}

// Gets the entities max health.
int Entity::GetMaxHealth() const
{
	return m_maxHealth;
}

// Gets the entities attack.
int Entity::GetAttack() const
{
	return m_attack;
}

// Gets the entities defense.
int Entity::GetDefense() const
{
	return m_defense;
}

// Gets the entities strength.
int Entity::GetStrength() const
{
	return m_strength;
}

// Gets the entities dexterity.
int Entity::GetDexterity() const
{
	return m_dexterity;
}

// Gets the entities stamina.
int Entity::GetStamina() const
{
	return m_stamina;
}

// Gets the entities accuracy.
int Entity::GetAccuracy() const
{
    return m_accuracy;
}

// Sets the entities attack stat.
void Entity::SetAttack(int attackValue)
{
	m_attack = attackValue;
}

// Sets the entities defense stat.
void Entity::SetDefense(int defenseValue)
{
	m_defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::SetStrength(int strengthValue)
{
	m_strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::SetDexterity(int dexterityValue)
{
	m_dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::SetStamina(int staminaValue)
{
	m_stamina = staminaValue;
}

// Sets the entities accuracy
void Entity::SetAccuracy(int accuracyValue)
{
    m_accuracy = accuracyValue;
}
