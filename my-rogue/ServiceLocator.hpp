//
//  ServiceLocator.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 14/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef ServiceLocator_hpp
#define ServiceLocator_hpp

#include "Audio.hpp"
#include "SFMLTexture.hpp"

class ServiceLocator
{
public:
    static void ProvideAudio(std::shared_ptr<Audio> audio);
    static std::shared_ptr<Audio> GetAudio();
    
    static void ProvideTexture(std::shared_ptr<SFMLTexture> audio);
    static std::shared_ptr<SFMLTexture> GetTexture();

private:
    ServiceLocator();
    
    static std::shared_ptr<Audio> m_audio;
    static std::shared_ptr<SFMLTexture> m_texture;
};

#endif /* ServiceLocator_hpp */
