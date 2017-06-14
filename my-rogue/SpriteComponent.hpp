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
     * @param component the transform component
     */
    void SetTransformComponent(std::shared_ptr<TransformComponent> component);
    
    /**
     * Draws the object to the screen at its current position.
     * @param window The render window to draw the object to.
     * @param tileDelta The time, in MS, since the last draw call.
     */
    void Draw(sf::RenderWindow &window, float timeDelta);
    
    /**
     * Creates and sets the object sprite.
     * This function takes the location to a resource, and from that create a texture and sprite.
     * You can optionally specify animation properties. If set the frame dimensions will be calculated automatically.
     * If left blank, the whole resource will be used.
     * @param fileName The path to the resource that you wish to load, relative to the project.
     * @param frames The number of frames in the sprite. Defaults to 1.
     * @param frameSpeed The speed that the animation plays at. Defaults to 1.
     * @return true if the operation succeeded.
     */
    bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
    
    /**
     * Returns a reference the object's sprite.
     * @return A reference to the object's sprite.
     */
    sf::Sprite& GetSprite();
    
    /**
     * Get the number of frames the object has.
     * @return The number of frames the object has.
     */
    int GetFrameCount() const;
    
    /**
     * Gets the current animation state of the object.
     * @return The current animation state of the object.
     */
    bool IsAnimated();
    
    /**
     * Sets the animation state of the object.
     * @param isAnimated The new animation state of the object.
     */
    void SetAnimated(bool isAnimated);

private:
    /**
     * Advances the sprite by a frame.
     */
    void NextFrame();
    
    
private:
    
    /**
     * Used to get the position the sprite should be rendered at
     */
    std::shared_ptr<TransformComponent> m_transformComponent;
    
    /**
     * The object's sprite.
     */
    sf::Sprite m_sprite;
    
    /**
     * The animation speed of the image if applicable.
     * Value is frames per second.
     */
    int m_animationSpeed;
    
    /**
     * Used to determine if the given sprite is animated.
     */
    bool m_isAnimated;
    
    /**
     * The total number of frames the sprite has.
     */
    int m_frameCount;
    
    /**
     * The current frame of the sprite.
     */
    int m_currentFrame;
    
    /**
     * The width of each frame of the animated sprite if applicable.
     */
    int m_frameWidth;
    
    /**
     * The height of each frame of the animated sprite if applicable.
     */
    int m_frameHeight;
    
    /**
     * An aggregate of the time passed between draw calls.
     */
    float m_timeDelta;
    
};

#endif /* SpriteComponent_hpp */
