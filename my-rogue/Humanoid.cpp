#include "PCH.hpp"
#include "Humanoid.hpp"
#include "ResourcePath.hpp"

#include "SpriteComponent.hpp"
#include "AnimationStateComponent.hpp"

#include <iostream>
#include <sstream>

// Default constructor.
Humanoid::Humanoid()
{
    // Randomise the type of humanoid enemy
    ENEMY_HUMANOIDS humanoidType = static_cast<ENEMY_HUMANOIDS>(rand() % static_cast<int>(ENEMY_HUMANOIDS::COUNT));
    
    std::string enemyName = "";
    
    switch (humanoidType)
    {
        case ENEMY_HUMANOIDS::SKELETON:
            enemyName = "skeleton";
            break;
        case ENEMY_HUMANOIDS::GOBLIN:
            enemyName = "goblin";
            break;
        case ENEMY_HUMANOIDS::COUNT:
            // error!
            break;
    }
    
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_left.png");
    
    // Copy textures ID
    // These are the default textures for a humanoid
    // Some will be replaced by 'armored' versions
    for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); ++i)
    {
        m_textures[i] = TextureManager::GetTexture(m_textureIDs[i]);
    }
    
    // Use a randomised color and size for gobbos
    // scale between 0.5 and 1.5
    if(humanoidType == ENEMY_HUMANOIDS::GOBLIN)
    {
        float scale = ((std::rand() % 6)/10.f) + 0.7f;
        GetComponent<SpriteComponent>()->GetSprite().setScale(scale, scale);
        
        // base goblin color
        sf::Color color(54,133,52,255);
        
        // randomise color elements
        // doesnt work as it splats the armor color as well...
        int r = (std::rand() % 100) - 50;
        int g = (std::rand() % 100) - 50;
        int b = (std::rand() % 100) - 50;
        
        sf::Color newColor(color.r + r, color.g + g, color.b + b, 255);
        
        // Color each of the goblin base textures
        // Can't just set the sprite color as the armor will be effected too
        for(int i=0; i<static_cast<int>(ANIMATION_STATE::COUNT); i++)
        {
            sf::RenderTexture target;
            sf::Sprite tempSprite;
            
            // Change the sprite color
            tempSprite.setTexture(m_textures[i]);
            tempSprite.setColor(newColor);
            
            // Save it out to a rendertexture
            target.create(m_textures[i].getSize().x, m_textures[i].getSize().y);
            target.clear(sf::Color(255,255,255,0));
            target.draw(tempSprite);
            target.display();
            
            // Replace the original texture with the recolored one
            m_textures[i] = target.getTexture();
            
        }
    }
    
    GenerateArmor();
    
	// Set initial sprite.
	GetComponent<SpriteComponent>()->SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
    GetComponent<SpriteComponent>()->SetAnimated(false);
}


void Humanoid::Update(float timeDelta)
{
    // Call parent update
    Enemy::Update(timeDelta);
    
    // Update texture with custom texture
    int textureIndex = static_cast<int>(GetComponent<AnimationStateComponent>()->GetState());
    GetComponent<SpriteComponent>()->GetSprite().setTexture(m_textures[textureIndex]);
}

// Generate random armor for this enemy
void Humanoid::GenerateArmor()
{
    // Create arrays of textures
    const int textureCount = static_cast<int>(ANIMATION_STATE::COUNT);
    sf::RenderTexture armorTextures[textureCount]; // Each layer of armor gets rendered here first
    
    for(int i=0; i<textureCount; i++)
    {
        sf::Vector2u textureSize = m_textures[i].getSize();
        armorTextures[i].create(textureSize.x, textureSize.y);
        armorTextures[i].clear(sf::Color(255,255,255,0));
        
        // copy the monster texture into the armor texture
        sf::Sprite tempSprite;
        tempSprite.setTexture(m_textures[i], true);
        armorTextures[i].draw(tempSprite);
    }
    
    int hasHelmet = std::rand() % 5;
    int hasTorso = std::rand() % 5;
    int hasLegs = std::rand() % 5;
    
    // Spawn helmet
    if(hasHelmet == 0)
    {
        // Load the helmet textures for each animation state
        int defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_walk_front.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_walk_front.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_walk_side.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_walk_side.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_idle_front.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "resources/armor/helmet/spr_helmet_idle_front.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_idle_side.png");
        defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/helmet/spr_helmet_idle_side.png");
        
        // Determine tier of helmet
        sf::Color tierColor;
        int tierValue = std::rand() & 100 + 1;
        //int tierValue = 99;
        
        if (tierValue < 51) {
            tierColor = sf::Color(110, 55, 28, 255); // Bronze.
        }
        else if (tierValue < 86)
        {
            tierColor = sf::Color(209, 208, 201, 255); // Silver.
        }
        else
        {
            tierColor = sf::Color(229, 192, 21, 255); // Gold.
        }
        
        // Render the colored helmet to the armor texture
        for (int i=0; i<static_cast<int>(ANIMATION_STATE::COUNT); i++) {
            // Load the default helmet texture and set its color.
            sf::Sprite tempSprite;
            tempSprite.setTexture(TextureManager::GetTexture(defaultHelmetTextureIDs[i]));
            tempSprite.setColor(tierColor);
            
            armorTextures[i].draw(tempSprite);
        }
    }

    // Spawn torso
    if(hasTorso == 0)
    {
        // Load the torso textures for each animation state
        int defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_walk_front.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_walk_front.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_walk_side.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_walk_side.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_idle_front.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "resources/armor/torso/spr_torso_idle_front.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_idle_side.png");
        defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/torso/spr_torso_idle_side.png");
        
        // Determine tier of torso
        sf::Color tierColor;
        int tierValue = std::rand() & 100 + 1;
        
        if (tierValue < 51) {
            tierColor = sf::Color(110, 55, 28, 255); // Bronze.
        }
        else if (tierValue < 86)
        {
            tierColor = sf::Color(209, 208, 201, 255); // Silver.
        }
        else
        {
            tierColor = sf::Color(229, 192, 21, 255); // Gold.
        }
        
        // Render the colored torso to the armor texture
        for (int i=0; i<static_cast<int>(ANIMATION_STATE::COUNT); i++) {
            // Load the default helmet texture and set its color.
            sf::Sprite tempSprite;
            tempSprite.setTexture(TextureManager::GetTexture(defaultTorsoTextureIDs[i]));
            tempSprite.setColor(tierColor);
            
            armorTextures[i].draw(tempSprite);
        }
    }
    
    // Spawn legs
    if(hasLegs == 0)
    {
        // Load the legs textures for each animation state
        int defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_walk_front.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_walk_front.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_walk_side.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_walk_side.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_idle_front.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(resourcePath() + "resources/armor/legs/spr_legs_idle_front.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_idle_side.png");
        defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(resourcePath() + "/resources/armor/legs/spr_legs_idle_side.png");
        
        // Determine tier of legs
        sf::Color tierColor;
        int tierValue = std::rand() & 100 + 1;
        
        if (tierValue < 51) {
            tierColor = sf::Color(110, 55, 28, 255); // Bronze.
        }
        else if (tierValue < 86)
        {
            tierColor = sf::Color(209, 208, 201, 255); // Silver.
        }
        else
        {
            tierColor = sf::Color(229, 192, 21, 255); // Gold.
        }
        
        // Render the colored legs to the armor texture
        for (int i=0; i<static_cast<int>(ANIMATION_STATE::COUNT); i++) {
            // Load the default helmet texture and set its color.
            sf::Sprite tempSprite;
            tempSprite.setTexture(TextureManager::GetTexture(defaultLegsTextureIDs[i]));
            tempSprite.setColor(tierColor);
            
            armorTextures[i].draw(tempSprite);
        }
    }

    // Create the final textures
    for (int i=0 ; i<static_cast<int>(ANIMATION_STATE::COUNT); i++) {
        
        // process all the data sent to the rendertexture
        armorTextures[i].display();
        
        // save it to an image
        sf::Image img = armorTextures[i].getTexture().copyToImage();
        
        // then load into the texture array
        m_textures[i].loadFromImage(img);
        
        // Debug code: save the texture to disk.
        /*if ((hasHelmet == 0) || (hasTorso == 0) || (hasLegs == 0))
        {
            std::stringstream stream;
            stream << resourcePath() + "/resources/test_" << i << ".png";
            img.saveToFile(stream.str());
        }*/
    }
    
}
