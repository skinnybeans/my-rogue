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
#include "AnimationFramesComponent.hpp"

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
     * Sets the animation frames component that controls the animation of a texture
     */
    void SetAnimationFramesComponent(std::shared_ptr<AnimationFramesComponent> component);
    
    /**
     * Draws the object to the screen at its current position.
     * @param window The render window to draw the object to.
     * @param tileDelta The time, in MS, since the last draw call.
     */
    //void Draw(sf::RenderWindow &window, float timeDelta);
    
    // New draw function, a AnimationFramesComponent takes care of all the time based stuff
    void Draw(sf::RenderWindow &window);
    
    /**
     * Stop direct access to the sf::Sprite for setting the texture
     */
    void SetTexture(sf::Texture& texture);
    
    /**
     * Handles setting the sprite frame correctly with the info in an animated texture
     */
    void SetAnimatedTexture(AnimatedTexture& animatedTexture);
    
    /**
     * Returns a reference the object's sprite.
     * TODO: remove this. should not provide direct access to the sprite
     * @return A reference to the object's sprite.
     */
    sf::Sprite& GetSprite();

private:
    /**
     * Sets the next frame of the texture to display
     */
    void SetFrameRect(sf::IntRect frameRect);
    
    
private:
    
    /**
     * Used to get the position the sprite should be rendered at
     */
    std::shared_ptr<TransformComponent> m_transformComponent;
    
    /**
     * Used to animate a texture
     */
    std::shared_ptr<AnimationFramesComponent> m_animationFramesComponent;
    
    /**
     * The object's sprite.
     */
    sf::Sprite m_sprite;
};

#endif /* SpriteComponent_hpp */
