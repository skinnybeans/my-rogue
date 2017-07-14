#include "PCH.hpp"
#include "Player.hpp"
#include "ResourcePath.hpp"

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "AnimationStateComponent.hpp"
#include "AnimationFramesComponent.hpp"

#include <algorithm>
#include <random>
#include <iostream>

// Constructor.
Player::Player() :
m_attackDelta(0.f),
m_damageDelta(0.f),
m_manaDelta(0.f),
m_isAttacking(false),
m_canTakeDamage(true)
{
    // Choose a random class
    m_class = static_cast<PLAYER_CLASS>(rand() % static_cast<int>(PLAYER_CLASS::COUNT));
    // Get class name to assist with loadingvplayer textures
    std::string m_className;
    switch(m_class)
    {
        case PLAYER_CLASS::WARRIOR:
            m_className = "warrior";
            break;
        case PLAYER_CLASS::THIEF:
            m_className = "thief";
            break;
        case PLAYER_CLASS::MAGE:
            m_className = "mage";
            break;
        case PLAYER_CLASS::ARCHER:
            m_className = "archer";
            break;
        case PLAYER_CLASS::COUNT:
            // errors...
            break;
    }
    
	// Load textures.
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_walk_up.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_walk_down.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_walk_right.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_walk_left.png", 8);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_idle_up.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_idle_down.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_idle_right.png", 1);
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/players/" + m_className + "/spr_" + m_className + "_idle_left.png", 1);
    
	// Get initial texture
    AnimatedTexture& spriteTexture = TextureManager::GetAnimatedTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)]);

    // Set the texture on the sprite
    GetComponent<SpriteComponent>()->SetAnimatedTexture(spriteTexture);
    
    // Set the animcation speed
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);

	// Create the player's aim sprite.
	int textureID = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_aim.png");
	m_aimSprite.setTexture(TextureManager::GetTexture(textureID));
	m_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
	m_aimSprite.setScale(2.f, 2.f);

	// Set stats.
    m_statPoints = 60;
    
    // determine stat distribution
    float attackBias = std::rand() % 101;
    float defenseBias = std::rand() % 101;
    float strengthBias = std::rand() % 101;
    float dexterityBias = std::rand() % 101;
    float staminaBias = std::rand() % 101;
    float accuracyBias = std::rand() % 101;
    
    float total =   attackBias +
                    defenseBias +
                    strengthBias +
                    dexterityBias +
                    staminaBias +
                    accuracyBias;

	m_attack = m_statPoints * (attackBias/total);
	m_defense = m_statPoints * (defenseBias/total);
	m_strength = m_statPoints * (strengthBias/total);
	m_dexterity = m_statPoints * (dexterityBias/total);
	m_stamina = m_statPoints * (staminaBias/total);
    m_accuracy = m_statPoints * (accuracyBias/total);
    
    // Modify stats based on class
    switch(m_class)
    {
        case PLAYER_CLASS::WARRIOR:
            m_strength += std::rand() %6 + 5;
            break;
        case PLAYER_CLASS::THIEF:
            m_accuracy += std::rand() %6 + 5;
            break;
        case PLAYER_CLASS::MAGE:
            m_defense += std::rand() %6 + 5;
            break;
        case PLAYER_CLASS::ARCHER:
            m_dexterity += std::rand() %6 + 5;
            break;
        case PLAYER_CLASS::COUNT:
            // errors...
            break;
    }
    
    // Modify stats based on traits
    SetRandomTraits();
    
    // Set derived stats
    m_health = m_maxHealth = 100 + m_stamina;
    m_mana = m_maxMana = 50;
    m_speed = 200 + m_dexterity;

}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = GetComponent<TransformComponent>()->GetPosition();
    sf::Vector2f nextPosition = previousPosition;

	
    // Set the movement speed based on player input
    if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
	{
		movementSpeed.x = -m_speed * timeDelta;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
	{
		movementSpeed.x = m_speed * timeDelta;
	}

	if (Input::IsKeyPressed(Input::KEY::KEY_UP))
	{
		movementSpeed.y = -m_speed * timeDelta;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
	{
		movementSpeed.y = m_speed * timeDelta;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		nextPosition.x = previousPosition.x;
	}
	else
	{
		nextPosition.x += movementSpeed.x;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		nextPosition.y = previousPosition.y;
	}
	else
	{
		nextPosition.y += movementSpeed.y;
	}
    
    // Set player's position
    GetComponent<TransformComponent>()->SetPosition(nextPosition);
    
    // Update animcation state
    std::shared_ptr<AnimationStateComponent> animationStateComponent = GetComponent<AnimationStateComponent>();
    animationStateComponent->Update(movementSpeed);

    // get the sprite component
    std::shared_ptr<SpriteComponent> spriteComponent = GetComponent<SpriteComponent>();
    
    // Update sprite if animation state changed
    if (animationStateComponent->HasStateChanged())
    {
        // AnimationState knows which texture should be used given the current entity movement
        int textureIndex = static_cast<int>(animationStateComponent->GetState());
        AnimatedTexture& spriteTexture = TextureManager::GetAnimatedTexture(m_textureIDs[textureIndex]);
        
        // Update the sprite with the new texture
        GetComponent<SpriteComponent>()->SetAnimatedTexture(spriteTexture);
    }

	// Calculate aim based on mouse.
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	m_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

	// Check if shooting.
	if ((m_attackDelta += timeDelta) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			// Mark player as attacking.
			m_isAttacking = true;
		}
	}

	// Determine if the player can take damage.
	if (!m_canTakeDamage)
	{
		if ((m_damageDelta += timeDelta) > 1.f)
		{
			m_canTakeDamage = true;
			m_damageDelta = 0.f;
		}
	}

	// Increase player mana.
	if ((m_manaDelta += timeDelta) > 0.20)
	{
		if (m_mana < m_maxMana)
		{
			m_mana += 1;
		}

		m_manaDelta = 0.f;
	}
}

// Returns the player's class
PLAYER_CLASS Player::GetPlayerClass() const
{
    return m_class;
}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
	return m_aimSprite;
}

// Return player traits
std::vector<PLAYER_TRAIT>* Player::GetPlayerTraits()
{
    return &m_traits;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
	if (m_isAttacking)
	{
		m_isAttacking = false;
		m_attackDelta = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if the player can take damage.
bool Player::CanTakeDamage()
{
	return m_canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
    m_health -= damage;

	if (m_health < 0)
	{
		m_health = 0;
	}

	m_canTakeDamage = false;
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
    Tile* overlappingTiles[4] = {nullptr,nullptr,nullptr,nullptr};
	sf::Vector2f newPosition = GetComponent<TransformComponent>()->GetPosition() + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (overlappingTiles[i] != nullptr && level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}

// Gets the player's mana.
int Player::GetMana() const
{
	return m_mana;
}

// Gets the player's max mana.
int Player::GetMaxMana() const
{
	return m_maxMana;
}

// Set the player's mana level.
void Player::SetMana(int manaValue)
{
	if (manaValue >= 0)
	{
		m_mana = manaValue;
	}
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	m_health = healthValue;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

// Set random traits for the player
void Player::SetRandomTraits()
{
    m_traits.clear();
    
    // Vector to shuffle traits
    std::vector<int> traits;
    traits.resize(static_cast<int>(PLAYER_TRAIT::COUNT));
    
    for(int i=0; i< static_cast<int>(PLAYER_TRAIT::COUNT); i++){
        traits.at(i) = i;
    }
    
    std::shuffle(traits.begin(), traits.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
    
    // Generate random traits
    for (int i = 0; i < PLAYER_TRAIT_COUNT && i < static_cast<int>(PLAYER_TRAIT::COUNT); i++) {
        m_traits.push_back(static_cast<PLAYER_TRAIT>(traits.at(i)));
    }
    
    // Apply the traits to the player
    for(PLAYER_TRAIT trait : m_traits)
    {
        switch (trait)
        {
            case PLAYER_TRAIT::ATTACK:
                m_attack += rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::DEFENSE:
                m_defense += std::rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::STRENGTH:
                m_strength += std::rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::DEXTERITY:
                m_dexterity += std::rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::STAMINA:
                m_stamina += std::rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::ACCURACY:
                m_accuracy += std::rand() % 6 + 5;
                break;
            case PLAYER_TRAIT::COUNT:
                // error!
                break;
        }
    }
}
