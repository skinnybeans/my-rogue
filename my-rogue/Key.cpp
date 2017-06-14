#include "PCH.hpp"
#include "Key.hpp"
#include "ResourcePath.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"

// Default constructor.
Key::Key()
{
	// Set item sprite.
	int textureID = TextureManager::AddTexture(resourcePath() + "/resources/loot/key/spr_pickup_key.png");
	GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

    // Attach a text component for the key
    AttachComponent<TextComponent>();
    
    // Give the text component the transform component so it knows where to render
    GetComponent<TextComponent>()->SetTransformComponent(GetComponent<TransformComponent>());
    
	// Set item text
    GetComponent<TextComponent>()->SetText("Key");

	// Set item type.
	m_type = ITEM::KEY;
}
