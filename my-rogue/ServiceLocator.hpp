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

class ServiceLocator
{
public:
    static void ProvideAudio(std::shared_ptr<Audio> audio);
    static std::shared_ptr<Audio> GetAudio();

private:
    ServiceLocator();
    
    static std::shared_ptr<Audio> m_audio;
};

#endif /* ServiceLocator_hpp */
