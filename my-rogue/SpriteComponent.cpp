//
//  SpriteComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.hpp"
#include "SpriteComponent.hpp"

// Default constructor
SpriteComponent::SpriteComponent() :
m_transformComponent(nullptr)
{}

// Sets the transform component to use
void SpriteComponent::SetTransformComponent(std::shared_ptr<TransformComponent> component)
{
    m_transformComponent = component;
}
