//
//  SFMLTexture.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "SFMLTexture.hpp"

SFMLTexture::SFMLTexture()
{}

void SFMLTexture::Initialise()
{
    for(int i=0; i< static_cast<int>(TEXTURE_ID::COUNT); i++)
    {
        m_textures[i] = new SFMLAnimatedTexture(TextureStrings[i].texturePath, TextureStrings[i].animationFrames);
    }
}

void SFMLTexture::CleanUp()
{
    for(int i=0; i< static_cast<int>(TEXTURE_ID::COUNT); i++)
    {
        delete m_textures[i];
    }
}

sf::Texture SFMLTexture::GetTexture(TEXTURE_ID textureId)
{
    return m_textures[static_cast<int>(textureId)]->m_texture;
}

SFMLAnimatedTexture* SFMLTexture::GetAnimatedTexture(TEXTURE_ID textureId)
{
    return m_textures[static_cast<int>(textureId)];
}
