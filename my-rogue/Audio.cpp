//
//  Audio.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Audio.hpp"

#include <iostream>

Audio::Audio()
{
    // Load all the sound buffers at startup
    for(int i=0; i < static_cast<int>(SOUND_ID::COUNT); i++)
    {
        m_buffers[i].loadFromFile(resourcePath() + SoundStrings[i]);
    }
}

int Audio::PlaySound(SOUND_ID sound)
{
    int channel = GetFreeChannel();
    
    // Couldn't get a free channel..
    if(channel < 0)
        return -1;
    
    // Have to create a new sound, otherwise playing a relative sound
    // after a positional sound causes weirdness
    m_channels[channel] = sf::Sound();
    m_channels[channel].setBuffer(m_buffers[static_cast<int>(sound)]);
    m_channels[channel].setRelativeToListener(true);
    
    m_channels[channel].play();
    
    return channel;
}

int Audio::PlaySound(SOUND_ID sound, sf::Vector2f position)
{
    int channel = GetFreeChannel();
    
    // Couldn't get a free channel..
    if(channel < 0)
        return -1;
    
    m_channels[channel] = sf::Sound();
    m_channels[channel].setBuffer(m_buffers[static_cast<int>(sound)]);
    m_channels[channel].setRelativeToListener(false);
    
    // default 3d settings
    m_channels[channel].setMinDistance(80.f);
    m_channels[channel].setAttenuation(5.f);
    
    m_channels[channel].setPosition(position.x, position.y, 0);
    
    m_channels[channel].play();
    
    return channel;
}

void Audio::StopSound(int channelId)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId].stop();
    std::cout << "Stopping: " << channelId << std::endl;
}

void Audio::SetLooping(int channelId, bool looping)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId].setLoop(looping);
}

void Audio::SetPosition(int channelId, sf::Vector2f position)
{
    if(channelId < 0 || channelId > MAX_CHANNELS)
        return;
    
    m_channels[channelId].setPosition(position.x, position.y, 0);
}

void Audio::PlayMusic()
{
    int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;
    std::string fileName = resourcePath() + "/resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav";
    m_music.openFromFile(fileName);
    m_music.setVolume(100.f);
    m_music.setRelativeToListener(true);
    m_music.setLoop(true);
    m_music.play();
}

int Audio::GetFreeChannel()
{
    for(int i=0; i<MAX_CHANNELS; i++)
    {
        if(m_channels[i].getStatus() == sf::SoundSource::Status::Stopped)
        {
            return i;
        }
    }
    
    return -1;
}
