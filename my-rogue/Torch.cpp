#include "PCH.hpp"
#include "Torch.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"

// Default constructor.
Torch::Torch() :
m_brightness(1.f)
{
	// Set sprite.
	int textureID = TextureManager::AddAnimatedTexture(resourcePath() + "/resources/spr_torch.png", 5);
    
	GetComponent<SpriteComponent>()->SetAnimatedTexture(TextureManager::GetAnimatedTexture(textureID));
    GetComponent<AnimationFramesComponent>()->SetFrameSpeed(12);
}

// Update the brightness of the torch.
void Torch::Update(float timeDelta)
{
	// Generate a random number between 80 and 120, divide by 100 and store as float between .8 and 1.2.
	m_brightness = (std::rand() % 41 + 80) / 100.f;
}

// Returns the brightness of the torch.
float Torch::GetBrightness()
{
	return m_brightness;
}
