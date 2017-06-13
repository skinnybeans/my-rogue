//
//  TransformComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 8/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.hpp"
#include "TransformComponent.hpp"

// Default constructor
TransformComponent::TransformComponent() :
m_position({0.f, 0.f}),
m_rotationDegrees(0.f)
{}

// Set the position of the component
void TransformComponent::SetPosition(sf::Vector2f position)
{
    m_position = position;
}

// Get the position of the component
sf::Vector2f TransformComponent::GetPosition() const
{
    return m_position;
}

// Set the rotation of the component
void TransformComponent::SetRotationDegrees(float degrees)
{
    m_rotationDegrees = degrees;
}

// Get the rotation of the component
float TransformComponent::GetRotationDegrees()
{
    return m_rotationDegrees;
}
