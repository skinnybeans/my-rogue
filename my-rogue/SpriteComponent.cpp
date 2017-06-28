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
/*
void SpriteComponent::Draw(sf::RenderWindow &window, float timeDelta)
{
    // If the sprite has no position, then don't render it
    if(m_transformComponent == nullptr)
        return;
    
    // Update the sprite position before drawing
    m_sprite.setPosition(m_transformComponent->GetPosition());
    m_sprite.setRotation(m_transformComponent->GetRotationDegrees());
    
    // check if the sprite is animated
    if (m_isAnimated)
    {
        // add the elapsed time since the last draw call to the aggregate
        m_timeDelta += timeDelta;
        
        // check if the frame should be updated
        if (m_timeDelta >= (1.f / m_animationSpeed))
        {
            NextFrame();
            m_timeDelta = 0;
        }
    }
    
    window.draw(m_sprite);
}
*/

void SpriteComponent::Draw(sf::RenderWindow& window)
{
    // If the sprite has no position, then don't render it
    if(m_transformComponent == nullptr)
        return;
    
    // Update the sprite position before drawing
    m_sprite.setPosition(m_transformComponent->GetPosition());
    m_sprite.setRotation(m_transformComponent->GetRotationDegrees());
    
    // Update the frame
    SetFrameRect(m_animationFramesComponent->GetFrameRect());
    
    window.draw(m_sprite);
}
 
// Set the texture on the underlying sprite
void SpriteComponent::SetTexture(sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    
    m_animationFramesComponent->SetFrames(texture.getSize(), 1);
    SetFrameRect(m_animationFramesComponent->GetFrameRect());
    //SetFrameRect(sf::IntRect(0,0,texture.getSize().x, texture.getSize().y));
}

// Set the texture on the underlying sprite
void SpriteComponent::SetAnimatedTexture(AnimatedTexture& animatedTexture)
{
    // Update the sprite texture
    m_sprite.setTexture(animatedTexture.m_texture);
    
    // Update the animation frames based on the info with the texture
    m_animationFramesComponent->SetFrames(animatedTexture.m_texture.getSize(), animatedTexture.m_frameCount);
    
    // Reset the currently displayed frame
    SetFrameRect(m_animationFramesComponent->GetFrameRect());
}

// Set the texture frame rect
void SpriteComponent::SetFrameRect(sf::IntRect frameRect)
{
    // Check the texture fits the rect
    sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
    
    if(frameRect.left > textureSize.x || frameRect.top > textureSize.y)
    {
        m_sprite.setTextureRect(sf::IntRect(0,0,textureSize.x, textureSize.y));
    }
    else
    {
        m_sprite.setTextureRect(frameRect);
    }
    m_sprite.setOrigin(frameRect.width / 2.f, frameRect.height / 2.f);
}

// Returns the object's sprite.
sf::Sprite& SpriteComponent::GetSprite()
{
    return m_sprite;
}
