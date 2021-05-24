//
//  AnimatedTexture.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "AnimatedTexture.hpp"

SFMLAnimatedTexture::SFMLAnimatedTexture(std::string texturePath, int frameCount)
{
    m_texture.loadFromFile(texturePath);
    this->m_frameCount = frameCount;
    m_frameSize.x = m_texture.getSize().x / frameCount;
    m_frameSize.y = m_texture.getSize().y;
}
