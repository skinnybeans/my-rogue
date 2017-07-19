//
//  AnimatedTexture.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "AnimatedTexture.hpp"

AnimatedTexture::AnimatedTexture(sf::Texture& texture, int frameCount):
m_texture(texture),
m_frameCount(frameCount)
{
    CalculateFrameSize();
};

AnimatedTexture::AnimatedTexture(std::string texturePath, int frameCount)
{
    m_texture.loadFromFile(texturePath);
    this->m_frameCount = frameCount;
    
    CalculateFrameSize();
}

// TODO: make the returned reference const, other places should not be modifying it
// may cause lots of stuff to break though...
sf::Texture& AnimatedTexture::GetTexture()
{
    return m_texture;
}

int AnimatedTexture::GetFrameCount()
{
    return m_frameCount;
}

sf::Vector2u AnimatedTexture::GetFrameSize()
{
    return m_frameSize;
}

void AnimatedTexture::CalculateFrameSize()
{
    m_frameSize.x = m_texture.getSize().x / m_frameCount;
    m_frameSize.y = m_texture.getSize().y;
}
