//
//  SpriteComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "TransformComponent.hpp"

class SpriteComponent : public Component
{
public:
    /**
     * Default constructor
     */
    SpriteComponent();
    
    /**
     * Sets the transform component to use for positioning
     */
    void SetTransformComponent(std::shared_ptr<TransformComponent> component);
    
private:
    /**
     * Position of the component
     */
    sf::Vector2f m_position;
    
    /**
     * Used to get the position the sprite should be rendered at
     */
    std::shared_ptr<TransformComponent> m_transformComponent;
    
};

#endif /* SpriteComponent_hpp */
