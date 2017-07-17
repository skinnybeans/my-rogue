//
//  Audio.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 17/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef Audio_hpp
#define Audio_hpp

#include "PCH.hpp"
#include "SoundList.hpp"

class Audio
{
public:
    /**
     * Play a sound relative to the listener
     * @param sound The Id of the sound to play
     * @return The channel the sound is playing on
     */
    virtual int PlaySound(SOUND_ID sound) = 0;
    
    virtual ~Audio(){};
    
    virtual void Initialise() = 0;
    virtual void CleanUp() = 0;
    
    /**
     * Play a sound at the specified position
     * @param sound The Id of the sound to play
     * @param position Position to play the sound
     * @return The channel the sound is playing on
     */
    virtual int PlaySound(SOUND_ID sound, sf::Vector2f position) = 0;
    
    
    /**
     * Stop a sound that is playing
     * @param channelId the channel id to stop
     */
    virtual void StopSound(int channelId) = 0;
    
    /**
     * Set the sound on a channel to loop
     * @param channelId the channel id to change looping on
     * @param looping set the looping status of the sound
     */
    virtual void SetLooping(int channelId, bool looping) = 0;
    
    // Set the location of a sound that is already playing
    virtual void SetPosition(int channelId, sf::Vector2f position) = 0;
    
    // Play a music track
    virtual void PlayMusic() = 0;
private:
};

#endif /* Audio_hpp */
