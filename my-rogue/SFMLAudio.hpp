//
//  SFMLAudio.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef SFMLAudio_hpp
#define SFMLAudio_hpp

#include "PCH.hpp"
#include "SoundList.hpp"
#include "Audio.hpp"

class SFMLAudio : public Audio
{
public:
    
    /**
     * Default constructor.
     * Loads all of the sound buffers required.
     */
    SFMLAudio();
    
    virtual ~SFMLAudio();
    
    virtual void Initialise();
    
    /**
     * Cleans up resources used by this class
     * Because this class is referred to statically, the destruction order of
     * the SF resources was causing problems. Needed to delete all of the SF resources before
     * the program exits. Otherwise they are left open and throw errors.
     * Might change the ServiceLocator to a singleton so it is not static...
     */
    virtual void CleanUp();
    
    /**
     * Play a sound relative to the listener
     * @param sound The Id of the sound to play
     * @return The channel the sound is playing on
     */
    virtual int PlaySound(SOUND_ID sound);
    
    /**
     * Play a sound at the specified position
     * @param sound The Id of the sound to play
     * @param position Position to play the sound
     * @return The channel the sound is playing on
     */
    virtual int PlaySound(SOUND_ID sound, sf::Vector2f position);
    
    
    /**
     * Stop a sound that is playing
     * @param channelId the channel id to stop
     */
    virtual void StopSound(int channelId);
    
    /**
     * Set the sound on a channel to loop
     * @param channelId the channel id to change looping on
     * @param looping set the looping status of the sound
     */
    virtual void SetLooping(int channelId, bool looping);
    
    // Set the location of a sound that is already playing
    virtual void SetPosition(int channelId, sf::Vector2f position);
    
    // Play a music track
    virtual void PlayMusic();
    
    
private:
    int GetFreeChannel();
private:
    static const int MAX_CHANNELS = 20;
    
    // Channels to play sounds on
    sf::Sound* m_channels [MAX_CHANNELS];
    
    // keeps all the sound buffers in memory ready to play
    sf::SoundBuffer* m_buffers [static_cast<int>(SOUND_ID::COUNT)];
    
    sf::Music* m_music;
};

#endif /* SMFLAudio_hpp */
