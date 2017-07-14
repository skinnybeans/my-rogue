//
//  Audio.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef Audio_hpp
#define Audio_hpp

#include "PCH.hpp"
#include "SoundList.hpp"

class Audio
{
public:
    Audio();
    
    // Play a sound relative to the listner
    int PlaySound(SOUND_ID sound);
    
    // Play a sound at the specified position
    int PlaySound(SOUND_ID sound, sf::Vector2f position);
    
    
private:
    int GetFreeChannel();
private:
    static const int MAX_CHANNELS = 20;
    
    // Channels to play sounds on
    sf::Sound m_channels [MAX_CHANNELS];
    
    // keeps all the sound buffers in memory ready to play
    sf::SoundBuffer m_buffers [static_cast<int>(SOUND_ID::COUNT)];
};

#endif /* Audio_hpp */
