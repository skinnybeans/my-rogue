//
//  SpriteComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.hpp"
#include "SpriteComponent.hpp"

#include <iostream>

// Default constructor
SpriteComponent::SpriteComponent() :
m_transformComponent(nullptr),
m_animationFramesComponent(nullptr)
{}

// Sets the transform component to use
void SpriteComponent::SetTransformComponent(std::shared_ptr<TransformComponent> component)
{
    m_transformComponent = component;
}

// Sets the animation frames to use
void SpriteComponent::SetAnimationFramesComponent(std::shared_ptr<AnimationFramesComponent> component)
{
    m_animationFramesComponent = component;
}

// Draws the object to the given render window.
void SpriteComponent::Draw(sf::RenderWindow &window, float timeDelta)
{
    // If the sprite has no position, then don't render it
    if(m_transformComponent == nullptr)
        return;
    
    m_animationFramesComponent->Update(timeDelta);
    
    // Update the sprite position before drawing
    m_sprite.setPosition(m_transformComponent->GetPosition());
    m_sprite.setRotation(m_transformComponent->GetRotationDegrees());
    
    // Update the frame
    m_sprite.setTextureRect(m_animationFramesComponent->GetFrameRect());
    
    window.draw(m_sprite);
}
 
// Set the texture on the underlying sprite
void SpriteComponent::SetTexture(sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    
    // Any texture set this way is assumed to only have one frame
    m_animationFramesComponent->SetFrames(texture.getSize(), 1);
    
    // Reset the currently displayed frame
    sf::IntRect frameRect = m_animationFramesComponent->GetFrameRect();
    m_sprite.setOrigin(frameRect.width / 2.f, frameRect.height / 2.f);
    m_sprite.setTextureRect(frameRect);
}

// Set the texture on the underlying sprite
void SpriteComponent::SetAnimatedTexture(AnimatedTexture& animatedTexture)
{
    // Update the sprite texture
    m_sprite.setTexture(animatedTexture.GetTexture());
    
    // Update the animation frames based on the info with the texture
    m_animationFramesComponent->SetFrames(animatedTexture.GetTexture().getSize(), animatedTexture.GetFrameCount());
    
    // Reset the currently displayed frame
    sf::IntRect frameRect = m_animationFramesComponent->GetFrameRect();
    m_sprite.setOrigin(frameRect.width / 2.f, frameRect.height / 2.f);
    m_sprite.setTextureRect(frameRect);
}

// Returns the object's sprite.
sf::Sprite& SpriteComponent::GetSprite()
{
    return m_sprite;
}
