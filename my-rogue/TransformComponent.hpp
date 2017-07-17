//
//  TransformComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 8/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "Component.hpp"

class TransformComponent : public Component
{
public:
    /**
     * Default constructor
     */
    TransformComponent();
    
    /**
     * Virtual destructor to ensure correct deletion through base class pointers
     */
    virtual ~TransformComponent(){};
    
    /**
     * Set the position of the component
     * @param vector specifiying position
     */
    void SetPosition(sf::Vector2f position);
    
    /**
     * Sets the roatation of the component
     * @param rotation in degrees
     */
    void SetRotationDegrees(float degrees);
    
    /**
     * Gets the objects rotation in degrees
     * @return rotation in degrees
     */
    float GetRotationDegrees();
    
    /**
     * Get the position of the component
     * @return vector specifying the position
     */
    sf::Vector2f GetPosition() const;
    
private:
    /**
     * Position of the component
     */
    sf::Vector2f m_position;
    
    /**
     * Rotation of the component
     */
    float m_rotationDegrees;
    
};

#endif /* TransformComponent_hpp */
