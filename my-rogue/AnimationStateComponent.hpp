//
//  AnimationStateComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 22/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef AnimationStateComponent_hpp
#define AnimationStateComponent_hpp

#include "Component.hpp"
#include "Util.hpp"

class AnimationStateComponent : public Component
{
public:
    AnimationStateComponent();
    
    /**
     * Update the state of the animation
     * @param velocity The velocity of the entity
     */
    void Update(sf::Vector2f velocity);
    
    /**
     * Get the current animation state of the entity
     * @return the animation state of the object
     */
    ANIMATION_STATE GetState();
    
    /**
     * Checks if the state of the animation component has changed since the last call to Update
     * @return true if the state has changed since last call to Upadate()
     */
    bool HasStateChanged();
    
private:
    
    /**
     * Current animation state of the entity
     */
    ANIMATION_STATE m_animationState;
    
    /**
     * State of entity if moving
     */
    ANIMATION_STATE m_movingState;
    
    /**
     * State of entity if stationary
     */
    ANIMATION_STATE m_stationaryState;
    
    /**
     * Did the animation state change after the last update
     */
    bool m_hasStateChanged;
};

#endif /* AnimationStateComponent_hpp */
