//
//  SFMLTexture.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef SFMLTexture_hpp
#define SFMLTexture_hpp

#include "AnimatedTexture.hpp"
#include "TextureList.hpp"

class SFMLTexture {
public:
    SFMLTexture();
    
    void Initialise();
    void CleanUp();
    
    sf::Texture* GetTexture(TEXTURE_ID textureId);
    AnimatedTexture* GetAnimatedTexture(TEXTURE_ID textureId);
private:
    AnimatedTexture* m_textures[static_cast<int>(TEXTURE_ID::COUNT)];
};

#endif /* SFMLTexture_hpp */
