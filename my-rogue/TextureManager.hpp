//-------------------------------------------------------------------------------------
// TextureManager.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class AnimatedTexture {
public:
    AnimatedTexture(sf::Texture& texture, int frameCount):
    m_texture(texture),
    m_frameCount(frameCount)
    {};
    sf::Texture& m_texture;
    int m_frameCount;
    sf::Vector2u m_frameSize;
};

class TextureManager
{
public:
	/**
	 * Adds a texture to the manager and returns its id in the map.
	 * @param The path to the image to load.
	 * @return The id to the texture created, or the id in the map if it already exists.
	 */
	static int AddTexture(std::string filePath);
    
    static int AddAnimatedTexture(std::string filePath, int frameCount);

	/**
	 * Removes a texture from the manager from a given id.
	 * @param textureID The id of the texture to be removed.
	 */
	static void RemoveTexture(int textureID);

	/**
	 * Gets a texture from the texture manager from an ID.
	 * @param textureId The id of the texture to return.
	 * @return A const reference to the texture.
	*/
	static sf::Texture& GetTexture(int textureId);
    
    static AnimatedTexture& GetAnimatedTexture(int textureId);

private:
    /**
     * Default constructor.
     */
    TextureManager();
    
	/**
	 * A map of each texture name with its ID.
	 */
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> m_textures;
    
    static std::map<int, std::unique_ptr<AnimatedTexture>> m_animatedTextures;

	/**
	 * The current key value.
	 */
	static int m_currentId;
};
#endif
