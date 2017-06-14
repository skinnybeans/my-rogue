//
//  TextComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 14/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.cpp"
#include "TextComponent.hpp"
#include "ResourcePath.hpp"

// Default constructor
TextComponent::TextComponent() :
m_transformComponent(nullptr),
m_textOffset({0,0})
{
    // Load font.
    m_font.loadFromFile(resourcePath() + "/resources/fonts/ADDSBP__.TTF");
    m_text.setFont(m_font);
    
    // Setup the text.
    m_text.setCharacterSize(12);
    m_text.setString("");
}

void TextComponent::SetTransformComponent(std::shared_ptr<TransformComponent> transformComponent)
{
    m_transformComponent = transformComponent;
}

void TextComponent::SetText(std::string text)
{
    m_text.setString(text);
    
    // Store the text offset needed when drawing.
    m_textOffset = sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

std::string TextComponent::GetText()
{
    return m_text.getString();
}

void TextComponent::Draw(sf::RenderWindow& window, float timeDelta)
{
    // Get the items position out for setting text and sprite location
    sf::Vector2f position = m_transformComponent->GetPosition();
    
    // Draw the item name.
    m_text.setPosition(position.x - m_textOffset.x, (position.y - 30.f) - m_textOffset.y);
    window.draw(m_text);
}
