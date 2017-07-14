//
//  Audio.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 13/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Audio.hpp"

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
    
    m_channels[channel].setRelativeToListener(true);
    m_channels[channel].setBuffer(m_buffers[static_cast<int>(sound)]);
    m_channels[channel].play();
    
    return channel;
}

int Audio::PlaySound(SOUND_ID sound, sf::Vector2f position)
{
    int channel = GetFreeChannel();
    
    // Couldn't get a free channel..
    if(channel < 0)
        return -1;
    
    m_channels[channel].setRelativeToListener(false);
    m_channels[channel].setBuffer(m_buffers[static_cast<int>(sound)]);
    m_channels[channel].setPosition(position.x, position.y, 0);
    m_channels[channel].play();
    
    return channel;
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
