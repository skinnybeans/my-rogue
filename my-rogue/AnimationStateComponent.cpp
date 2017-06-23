//
//  AnimationStateComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 22/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.hpp"
#include "AnimationStateComponent.hpp"

#include <cmath>


// Default constructor
AnimationStateComponent::AnimationStateComponent() :
m_hasStateChanged(true),
m_stationaryState(ANIMATION_STATE::IDLE_DOWN),
m_movingState(ANIMATION_STATE::WALK_DOWN),
m_animationState(ANIMATION_STATE::IDLE_DOWN)
{}

// Get the current animation state
ANIMATION_STATE AnimationStateComponent::GetState()
{
    return m_animationState;
}

// Has the state changed since last update
bool AnimationStateComponent::HasStateChanged()
{
    return m_hasStateChanged;
}

// Update the animation state based on velocity
void AnimationStateComponent::Update(sf::Vector2f velocity)
{
    ANIMATION_STATE previousState = m_animationState;
    
    ANIMATION_STATE movingState;
    ANIMATION_STATE stationaryState;
    
    // If the entity is moving, we need to select new idle and moving animations
    // TODO: split the coupling of changing direction and changing animation state to clean this up
    if ((velocity.x != 0) || (velocity.y != 0))
    {
        if (std::abs(velocity.x) > std::abs(velocity.y))
        {
            if (velocity.x <= 0)
            {
                m_movingState = ANIMATION_STATE::WALK_LEFT;
                m_stationaryState = ANIMATION_STATE::IDLE_LEFT;
            }
            else
            {
                m_movingState = ANIMATION_STATE::WALK_RIGHT;
                m_stationaryState = ANIMATION_STATE::IDLE_RIGHT;
            }
        }
        else
        {
            if (velocity.y <= 0)
            {
                m_movingState = ANIMATION_STATE::WALK_UP;
                m_stationaryState = ANIMATION_STATE::IDLE_UP;
            }
            else
            {
                m_movingState = ANIMATION_STATE::WALK_DOWN;
                m_stationaryState = ANIMATION_STATE::IDLE_DOWN;
            }
        }
        // Set the current state to the moving state
        m_animationState = m_movingState;
    }
    else
    {
        // Direction hasn't changed, but make sure the stationary animation is selected
        // whichever direction the entitiy was last facing
        m_animationState = m_stationaryState;
    }
    
    if(previousState != m_animationState)
        m_hasStateChanged = true;
    else
        m_hasStateChanged = false;
}
