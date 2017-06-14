#include "PCH.hpp"
#include "Projectile.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

#include <iostream>
#include <cmath>

// Default constructor.
Projectile::Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f screenCenter, sf::Vector2f target)
{
	// Create the sprite.
	GetComponent<SpriteComponent>()->SetSprite(texture, false);

	// Set the position.
    GetComponent<TransformComponent>()->SetPosition(origin);

	// Calculate the velocity of the object.
	m_velocity = target - screenCenter;

    float length = std::sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;
}

// Update the projectile.
void Projectile::Update(float timeDelta)
{
    std::shared_ptr<TransformComponent> transformComponent = GetComponent<TransformComponent>();
	
    // Update rotation.
    // Set it on the transform component in prepareation for moving to sprite components
    float currentRotation = transformComponent->GetRotationDegrees();
    float newRoataion = currentRotation + (400.f * timeDelta);
    transformComponent->SetRotationDegrees(newRoataion);

	// Update position.
    sf::Vector2f currentPosition = transformComponent->GetPosition();
    sf::Vector2f newPosition(currentPosition.x + (m_velocity.x * (500 * timeDelta)), currentPosition.y + (m_velocity.y * (500 * timeDelta)));
    
    transformComponent->SetPosition(newPosition);
}
