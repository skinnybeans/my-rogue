//
//  Audio.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "ResourcePath.hpp"
#include "SFMLAudio.hpp"

#include <iostream>

// Default constructor
SFMLAudio::SFMLAudio()
{}

SFMLAudio::~SFMLAudio()
{}

void SFMLAudio::Initialise()
{
    // Load all the sound buffers at startup
    for(int i=0; i < static_cast<int>(SOUND_ID::COUNT); i++)
    {
        m_buffers[i] = new sf::SoundBuffer();
        m_buffers[i]->loadFromFile(resourcePath() + SoundStrings[i]);
    }
    
    for(int i=0; i<MAX_CHANNELS; i++)
    {
        m_channels[i] = new sf::Sound();
    }
    
    m_music = new sf::Music();
}

void SFMLAudio::CleanUp()
{
    for(int i=0; i<MAX_CHANNELS; i++)
    {
        m_channels[i]->stop();
        delete m_channels[i];
    }
    
    m_music->stop();
    delete m_music;
    
    for(int i=0; i < static_cast<int>(SOUND_ID::COUNT); i++)
    {
        delete m_buffers[i];
        m_buffers[i] = nullptr;
    }
}

// Play a sound effect relative to the listener
int SFMLAudio::PlaySound(SOUND_ID sound)
{
    int channel = GetFreeChannel();
    
    // Couldn't get a free channel..
    if(channel < 0)
        return -1;
    
    // Have to create a new sound, otherwise playing a relative sound
    // after a positional sound causes weirdness
    delete m_channels[channel];
    m_channels[channel] =  new sf::Sound();
    m_channels[channel]->setBuffer(*m_buffers[static_cast<int>(sound)]);
    m_channels[channel]->setRelativeToListener(true);
    
    m_channels[channel]->play();
    
    return channel;
}

// Play a sound effect at a 2D point
int SFMLAudio::PlaySound(SOUND_ID sound, sf::Vector2f position)
{
    int channel = GetFreeChannel();
    
    // Couldn't get a free channel..
    if(channel < 0)
        return -1;
    
    delete m_channels[channel];
    m_channels[channel] = new sf::Sound();
    m_channels[channel]->setBuffer(*m_buffers[static_cast<int>(sound)]);
    m_channels[channel]->setRelativeToListener(false);
    
    // default 3d settings
    m_channels[channel]->setMinDistance(80.f);
    m_channels[channel]->setAttenuation(5.f);
    
    m_channels[channel]->setPosition(position.x, position.y, 0);
    
    m_channels[channel]->play();
    
    return channel;
}

// Stop a sound playing on a channel
void SFMLAudio::StopSound(int channelId)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId]->stop();
}

// Set a sound to loop on a particular channel
void SFMLAudio::SetLooping(int channelId, bool looping)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId]->setLoop(looping);
}

// Set the position of a sound on a particular channel
void SFMLAudio::SetPosition(int channelId, sf::Vector2f position)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId]->setPosition(position.x, position.y, 0);
}

// Play a music track
void SFMLAudio::PlayMusic()
{
    /*
    int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;
    std::string fileName = resourcePath() + "/resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav";
    m_music.openFromFile(fileName);
    m_music.setVolume(100.f);
    m_music.setRelativeToListener(true);
    m_music.setLoop(true);
    m_music.play();
     */
}

// Get a channel that has no sounds playing on it
int SFMLAudio::GetFreeChannel()
{
    for(int i=0; i<MAX_CHANNELS; i++)
    {
        if(m_channels[i]->getStatus() == sf::SoundSource::Status::Stopped)
        {
            return i;
        }
    }
    return -1;
}
