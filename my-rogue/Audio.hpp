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
    
    // Stop a sound that is playing
    void StopSound(int channelId);
    
    // Set the sound on a channel to loop
    void SetLooping(int channelId, bool looping);
    
    // Set the location of a sound that is already playing
    void SetPosition(int channelId, sf::Vector2f position);
    
    // Play a music track
    void PlayMusic();
    
    
private:
    int GetFreeChannel();
private:
    static const int MAX_CHANNELS = 20;
    
    // Channels to play sounds on
    sf::Sound m_channels [MAX_CHANNELS];
    
    // keeps all the sound buffers in memory ready to play
    sf::SoundBuffer m_buffers [static_cast<int>(SOUND_ID::COUNT)];
    
    sf::Music m_music;
};

#endif /* Audio_hpp */
