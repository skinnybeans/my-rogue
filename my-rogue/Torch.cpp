#include "PCH.hpp"
#include "Torch.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

#include <iostream>

// Default constructor.
Torch::Torch()
{
	// Set sprite.
	int textureID = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/spr_torch.png", 5);
    
	GetComponent<SpriteComponent>()->SetAnimatedTexture(TextureManager::GetAnimatedTexture(textureID));
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);
    
    
    // Randomly set the transition speed: 0.1 -> 0.3 sec
    m_transitionSpeed = (std::rand() % 21 + 10) / 100.f;
    
    // Randomly set the starting intensity: 1.00 -> 1.40
    m_intensityCurrent = (std::rand() % 41 + 100) / 100.f;
    
    // Set the intensity range of the torch
    m_intensityBright = m_intensityCurrent + 0.1f;
    m_intensityDark = m_intensityCurrent - 0.1f;
    
    // Set the torch state
    m_state = static_cast<TORCH_STATE>(std::rand() % 2);
}

// Update the brightness of the torch.
void Torch::Update(float timeDelta)
{
    float intensityDelta = (m_intensityBright - m_intensityDark) * (1/m_transitionSpeed) * timeDelta;
    
    switch(m_state)
    {
        case TORCH_STATE::DARK:
        {
            m_intensityCurrent += intensityDelta;
            if(m_intensityCurrent >= m_intensityBright)
                m_state = TORCH_STATE::BRIGHT;
        }
            break;
        case TORCH_STATE::BRIGHT:
        {
            m_intensityCurrent -= intensityDelta;
            if(m_intensityCurrent <= m_intensityDark)
                m_state = TORCH_STATE::DARK;
        }
            break;
        case TORCH_STATE::COUNT:
            // error!
            break;
    }
}

// Returns the brightness of the torch.
float Torch::GetBrightness()
{
	return m_intensityCurrent;
}
