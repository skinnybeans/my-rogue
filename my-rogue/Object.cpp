#include "PCH.hpp"
#include "Object.hpp"

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

// Default constructor.
Object::Object()
{
    // Replace position with a transform component
    AttachComponent<TransformComponent>();
    
    // Component for sprites
    AttachComponent<SpriteComponent>();
    
    // Sprite needs access to position
    GetComponent<SpriteComponent>()->SetTransformComponent(GetComponent<TransformComponent>());
    
    // Add component to track animation frames
    AttachComponent<AnimationFramesComponent>();
    
    // Pass the animation frames component into the sprite
    GetComponent<SpriteComponent>()->SetAnimationFramesComponent(GetComponent<AnimationFramesComponent>());
}
