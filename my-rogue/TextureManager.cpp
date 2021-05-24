#include "PCH.hpp"

std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> TextureManager::m_textures;
int TextureManager::m_currentId = 0;

std::map<int, std::unique_ptr<AnimatedTexture>> TextureManager::m_animatedTextures;

// Default Constructor.
TextureManager::TextureManager()
{
}

// Adds a texture to the manager, and returns its id in the map.
int TextureManager::AddTexture(std::string filePath)
{
	// First check if the texture has already been created. If so, simply return that one.
	auto it = m_textures.find(filePath);

	if (it != m_textures.end())
	{
		return it->second.first;
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	m_currentId++;

	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    
	if (!texture->loadFromFile(filePath))
	{
		return -1;
	}

	m_textures.insert(std::make_pair(filePath, std::make_pair(m_currentId, std::move(texture))));

	// Return the texture.
	return m_currentId;
}

int TextureManager::AddAnimatedTexture(std::string filePath, int frameCount)
{
    int textureID = TextureManager::AddTexture(filePath);
    
    // See if the animated texture already exists
    auto it = m_animatedTextures.find(textureID);
    
    // If not create it with the matching texture ID from the raw texture storage
    if(it == m_animatedTextures.end())
    {
        std::unique_ptr<AnimatedTexture> animatedTexture = std::make_unique<AnimatedTexture>(TextureManager::GetTexture(textureID), frameCount);
        animatedTexture->m_frameSize = animatedTexture->m_texture.getSize();
        animatedTexture->m_frameSize.x /= frameCount;
        
        m_animatedTextures.insert(std::make_pair(textureID, std::move(animatedTexture)));
    }
    return textureID;
}

AnimatedTexture& TextureManager::GetAnimatedTexture(int textureID)
{
    auto it = m_animatedTextures.find(textureID);
    
    if(it != m_animatedTextures.end())
    {
        return *it->second;
    }
    
    return *m_animatedTextures.begin()->second;
}

// Removes a texture from the manager from a given id.
void TextureManager::RemoveTexture(int textureID)
{
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (it->second.first == textureID)
		{
			m_textures.erase(it->first);
		}
	}
}

// Gets a texture from the texture manager from an ID.
sf::Texture& TextureManager::GetTexture(int textureID)
{
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (it->second.first == textureID)
		{
			return *it->second.second;
		}
	}
}
