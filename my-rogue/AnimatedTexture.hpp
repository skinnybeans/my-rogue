//
//  AnimatedTexture.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef AnimatedTexture_hpp
#define AnimatedTexture_hpp

#include <SFML/Graphics.hpp>

class AnimatedTexture {
public:
    AnimatedTexture(sf::Texture& texture, int frameCount);
    AnimatedTexture(std::string texturePath, int frameCount);
    
    sf::Texture& GetTexture();
    int GetFrameCount();
    sf::Vector2u GetFrameSize();

private:
    void CalculateFrameSize();

private:
    sf::Texture m_texture;
    int m_frameCount;
    sf::Vector2u m_frameSize;
};
/*
class SFMLAnimatedTexture {
public:
    SFMLAnimatedTexture(std::string texturePath, int frameCount);
    sf::Texture m_texture;
    int m_frameCount;
    sf::Vector2u m_frameSize;
};
*/


#endif /* AnimatedTexture_hpp */
