//
//  TextureComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 23/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef TextureComponent_hpp
#define TextureComponent_hpp

#include "Component.hpp"
#include "PCH.hpp"
#include <string>

class TextureComponent : public Component
{
public:
    // Default constructor
    TextureComponent();
    
    void SetTexture(std::string texturePath, int frames);
    
    const sf::Texture GetTexture();
private:
    
    /**
     * ID of the texture
     */
    int m_textureID;
    
    /**
     * Number of frames the texture holds
     */
    int m_frameCount;
    
    int m_frameHeight;
    int m_frameWidth;
    
};

#endif /* TextureComponent_hpp */
