//
//  ServiceLocator.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 14/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "ServiceLocator.hpp"

#include <iostream>

std::shared_ptr<Audio> ServiceLocator::m_audio = nullptr;
std::shared_ptr<SFMLTexture> ServiceLocator::m_texture = nullptr;

void ServiceLocator::ProvideAudio(std::shared_ptr<Audio> audio)
{
    m_audio = audio;
}

std::shared_ptr<Audio> ServiceLocator::GetAudio()
{
    return m_audio;
}

void ServiceLocator::ProvideTexture(std::shared_ptr<SFMLTexture> texture)
{
    m_texture = texture;
}

std::shared_ptr<SFMLTexture> ServiceLocator::GetTexture()
{
    return m_texture;
}
