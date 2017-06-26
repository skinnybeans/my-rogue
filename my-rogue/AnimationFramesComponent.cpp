//
//  AnimationFramesComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 26/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "AnimationFramesComponent.hpp"
#include "PCH.hpp"

// Default constructor
AnimationFramesComponent::AnimationFramesComponent() :
m_elapsedTime(0.f),
m_frameSpeed(1.f)
{}

// Set the number of frames
void AnimationFramesComponent::SetFrames(sf::Vector2u textureSize, int frameCount)
{
    m_frameCount = frameCount;
    
    // Carve up the texture size into frames
    m_frameSize.x = textureSize.x / frameCount;
    m_frameSize.y = textureSize.y;
    
    m_currentFrame = 0;
    m_elapsedTime = 0.f;
    
    // Set the current frame
    CalculateRect();
}

// Set the speed of the frames
void AnimationFramesComponent::SetFrameSpeed(int framesPerSecond)
{
    m_frameSpeed = 1.f/framesPerSecond;
}

// Calculate the texture rect to use for the current frame
void AnimationFramesComponent::CalculateRect()
{
    sf::Vector2i origin;
    
    origin.x = m_currentFrame * m_frameSize.x;
    origin.y = 0;
    
    m_textureRect = sf::IntRect(origin, static_cast<sf::Vector2i>(m_frameSize));
}

sf::IntRect AnimationFramesComponent::GetFrameRect()
{
    return m_textureRect;
}

// Update the frame component
void AnimationFramesComponent::Update(float timeDelta)
{
    // If there is only 1 frame, don't bother updating
    if(m_frameCount == 1)
        return;
    
    m_elapsedTime += timeDelta;
    
    // Do we need to update the frame yet
    if(m_elapsedTime >= m_frameSpeed)
    {
        // Advance the frame count
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        
        // set the new texture rect
        CalculateRect();
        
        // reset the time accumulator
        m_elapsedTime = 0.f;
    }
}

void AnimationFramesComponent::Reset()
{
    m_elapsedTime = 0.f;
    m_frameCount = 0;
    CalculateRect();
}
