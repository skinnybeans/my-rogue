//
//  AnimationFramesComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 26/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef AnimationFramesComponent_hpp
#define AnimationFramesComponent_hpp

#include "PCH.hpp"
#include "Component.hpp"

class AnimationFramesComponent : public Component
{
public:
    /**
     * Default constructor
     */
    AnimationFramesComponent();
    
    /**
     * Sets the number and size of frames
     * @param textureSize total size of the texture
     * @param how many frames in the texture
     */
    void SetFrames(sf::Vector2u textureSize, int frameCount);
    
    /**
     * How many frames to display per second
     * @param framesPerSecond number of frames per second
     */
    void SetFrameSpeed(int framesPerSecond);
    
    /**
     * Update the animation frame
     */
    void Update(float timeDelta);
    
    /**
     *
     */
    sf::IntRect GetFrameRect();
    
private:
    void CalculateRect();

private:
    /**
     * Size of the frame
     */
    sf::Vector2u m_frameSize;
    
    /**
     * Number of frames
     */
    int m_frameCount;
    
    /**
     * Current frame index
     */
    int m_currentFrame;
    
    /**
     * The current texture rect
     */
    sf::IntRect m_textureRect;
    
    /**
     * Time between frames in seconds.
     */
    float m_frameSpeed;
    
    /**
     * Time elapsed since last frame update
     */
    float m_elapsedTime;
};

#endif /* AnimationFramesComponent_hpp */
