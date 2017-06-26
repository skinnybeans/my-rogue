//
//  TextureComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 23/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "PCH.hpp"
#include "TextureComponent.hpp"

TextureComponent::TextureComponent()
{}

void TextureComponent::SetTexture(std::string texturePath, int frames)
{
    m_textureID = TextureManager::AddTexture(texturePath);
    m_frameCount = frames;
}

const sf::Texture TextureComponent::GetTexture()
{
    
}
