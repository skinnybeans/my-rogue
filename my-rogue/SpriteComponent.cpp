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
m_animationSpeed(0),
m_isAnimated(false),
m_frameCount(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0)
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

bool SpriteComponent::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
    // Create a sprite from the loaded texture.
    m_sprite.setTexture(texture);
    
    // Set animation speed.
    m_animationSpeed = frameSpeed;
    
    // Store the number of frames.
    m_frameCount = frames;
    
    // Calculate frame dimensions.
    // This should live in a texture component...
    sf::Vector2u texSize = m_sprite.getTexture()->getSize();
    m_frameWidth = texSize.x / m_frameCount;
    m_frameHeight = texSize.y;
    
    // Check if animated or static.
    if (frames > 1)
    {
        // Set sprite as animated.
        m_isAnimated = true;
        
        // Set the texture rect of the first frame.
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
    else
    {
        // Set sprite as non animated.
        m_isAnimated = false;
    }
    
    // Set the origin of the sprite.
    m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);
    
    return true;
}

// Set the texture on the underlying sprite
void SpriteComponent::SetTexture(sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    
    // Have to wait until moving the enemies over to the new animation/texture handling for this to work!
    //SetFrameRect(sf::IntRect(0,0,texture.getSize().x, texture.getSize().y));
}

// Set the texture on the underlying sprite
void SpriteComponent::SetAnimatedTexture(AnimatedTexture& animatedTexture)
{
    m_sprite.setTexture(animatedTexture.m_texture);
    m_animationFramesComponent->SetFrames(animatedTexture.m_texture.getSize(), animatedTexture.m_frameCount);
    SetFrameRect(m_animationFramesComponent->GetFrameRect());
    
    //SetFrameRect(sf::IntRect(0, 0,animatedTexture.m_frameSize.x, animatedTexture.m_frameSize.y));
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

// Gets the current animation state of the object.
bool SpriteComponent::IsAnimated()
{
    return m_isAnimated;
}

// Sets the animation state of the object.
void SpriteComponent::SetAnimated(bool isAnimated)
{
    m_isAnimated = isAnimated;
    
    if (isAnimated)
    {
        m_currentFrame = 0;
    }
    else
    {
        // set the texture rect of the first frame
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
}

// Advances the sprite forward a frame.
void SpriteComponent::NextFrame()
{
    // check if we reached the last frame
    if (m_currentFrame == (m_frameCount - 1))
        m_currentFrame = 0;
    else
        m_currentFrame++;
    
    // update the texture rect
    m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

// Gets the frame count of the object.
int SpriteComponent::GetFrameCount() const
{
    return m_frameCount;
}
