#include "PCH.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "AnimationFramesComponent.hpp"

#include "BacktrackerLevelGenerator.hpp"
#include "OpenRoomLevelGenerator.hpp"

#include <cmath>
#include <iostream>

// Default constructor.
Game::Game(sf::RenderWindow* window) :
m_window(*window),
m_gameState(GAME_STATE::PLAYING),
m_isRunning(true),
m_string(""),
m_screenSize({ 0, 0 }),
m_screenCenter({ 0, 0 }),
m_scoreTotal(0),
m_goldTotal(0),
m_projectileTextureID(0),
m_levelWasGenerated(false),
m_hasActiveGoal(false)
{
	// Enable VSync.
	m_window.setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	m_window.setMouseCursorVisible(false);

	// Calculate and store the center of the screen.
	m_screenCenter = { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f };

	// Create the level object.
	m_level = Level();

	// Create the game font.
	m_font.loadFromFile(resourcePath() + "/resources/fonts/ADDSBP__.TTF");
    
    // Load music
    int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;
    m_music.openFromFile(resourcePath() + "/resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");
    m_music.setVolume(100.f);
    m_music.setRelativeToListener(true);
    m_music.setLoop(true);
    m_music.play();
}

// Initializes the game.
void Game::Initialize()
{
	// Get the screen size.
	m_screenSize = m_window.getSize();

	// Load the correct projectile texture based on player class
    std::string spriteName("");
    switch (m_player.GetPlayerClass()) {
        case PLAYER_CLASS::WARRIOR:
            spriteName = "sword";
            break;
        case PLAYER_CLASS::THIEF:
            spriteName = "dagger";
            break;
        case PLAYER_CLASS::MAGE:
            spriteName = "magic_ball";
            break;
        case PLAYER_CLASS::ARCHER:
            spriteName = "arrow";
            break;
        case PLAYER_CLASS::COUNT:
            // error!
            break;
    }
	
    m_projectileTextureID = TextureManager::AddTexture(resourcePath() + "/resources/projectiles/spr_" + spriteName + ".png");
    
    // Create the sound buffer manager
    m_soundBufferManager = std::make_shared<SoundBufferManager>();
    
    // Load all game sounds.
    int soundBufferId;
    
    // Load torch sound.
    soundBufferId = m_soundBufferManager->AddSoundBuffer(resourcePath() + "/resources/sounds/snd_fire.wav");
    m_fireSound.setBuffer(m_soundBufferManager->GetSoundBuffer(soundBufferId));
    m_fireSound.setLoop(true);
    m_fireSound.setMinDistance(80.f);
    m_fireSound.setAttenuation(5.f);
    m_fireSound.play();
    
    
    // Load enemy die sound.
    soundBufferId = m_soundBufferManager->AddSoundBuffer(resourcePath() + "/resources/sounds/snd_enemy_dead.wav");
    m_enemyDieSound.setBuffer(m_soundBufferManager->GetSoundBuffer(soundBufferId));
    m_enemyDieSound.setMinDistance(80.f);
    m_enemyDieSound.setAttenuation(5.f);

	// Initialize the UI.
	LoadUI();

	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = m_window.getDefaultView();
	//m_views[static_cast<int>(VIEW::MAIN)].zoom(0.75f);
    m_views[static_cast<int>(VIEW::MAIN)].zoom(1.0f);
	m_views[static_cast<int>(VIEW::UI)] = m_window.getDefaultView();
    
    GenerateLevel();
}

// Constructs the grid of sprites that are used to draw the game light system.
void Game::ConstructLightGrid()
{
    // Ensure the grid is cleared from the previous level
    m_lightGrid.clear();
    
	// Load the light tile texture and store a reference.
	int textureID = TextureManager::AddTexture(resourcePath() + "/resources/spr_light_grid.png");
	sf::Texture& lightTexture = TextureManager::GetTexture(textureID);

	// Calculate the number of tiles in the grid. Each light tile is 25px square.
	sf::IntRect levelArea;

	// Define the bounds of the level.
    levelArea.left = 0;
    levelArea.top = 0;
	levelArea.width = m_level.GetSize().x * m_level.GetTileSize();
	levelArea.height = m_level.GetSize().y * m_level.GetTileSize();

	int width, height, lightTotal;

	width = levelArea.width / 25;
	height = levelArea.height / 25;

	lightTotal = width * height;

	// Create all tiles.
	for (int i = 0; i < lightTotal; i++)
	{
		// Create the tile.
		sf::Sprite lightSprite;

		// Set sprite texture.
		lightSprite.setTexture(lightTexture);

		// Set the position of the tile.
		int xPos = levelArea.left + ((i % width) * 25);
		int yPos = levelArea.top + ((i / width) * 25);

		lightSprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

		// Add the sprite to our light vector.
		m_lightGrid.push_back(lightSprite);
	}
}

// Loads and prepares all UI assets.
void Game::LoadUI()
{
	// Initialize the player ui texture and sprite.
    std::string className;
    switch(m_player.GetPlayerClass())
    {
        case PLAYER_CLASS::WARRIOR:
            className = "warrior";
            break;
        case PLAYER_CLASS::THIEF:
            className = "thief";
            break;
        case PLAYER_CLASS::MAGE:
            className = "mage";
            break;
        case PLAYER_CLASS::ARCHER:
            className = "archer";
            break;
        case PLAYER_CLASS::COUNT:
            // errors...
            break;
    }
    
	m_playerUiSprite = std::make_shared<sf::Sprite>();
	m_playerUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_" + className + "_ui.png")));
	m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
	m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
	m_uiSprites.push_back(m_playerUiSprite);

	// Bar outlines.
	sf::Texture& barOutlineTexture = TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_bar_outline.png"));
	sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };

	m_healthBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_healthBarOutlineSprite->setTexture(barOutlineTexture);
	m_healthBarOutlineSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_healthBarOutlineSprite);

	m_manaBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_manaBarOutlineSprite->setTexture(barOutlineTexture);
	m_manaBarOutlineSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_manaBarOutlineSprite);

	//Bars.
	sf::Texture& healthBarTexture = TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_health_bar.png"));
	sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };

    // When scaling the UI, need to move the health bar texture position to the right location
    // So it lines up with the bar outline
    float barOffset = ((205.f - (205.f * UI_SCALE)) / 2.f) + 1.f;
	m_healthBarSprite = std::make_shared<sf::Sprite>();
	m_healthBarSprite->setTexture(healthBarTexture);
	m_healthBarSprite->setPosition(sf::Vector2f(205.f + barOffset, 35.f));
	m_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_manaBarSprite = std::make_shared<sf::Sprite>();
	m_manaBarSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_mana_bar.png")));
	m_manaBarSprite->setPosition(sf::Vector2f(205.f + barOffset, 55.f));
	m_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	// Initialize the coin and gem ui sprites.
	m_gemUiSprite = std::make_shared<sf::Sprite>();
	m_gemUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_gem_ui.png")));
	m_gemUiSprite->setPosition(sf::Vector2f(m_screenCenter.x - 260.f, 50.f));
	m_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
	m_uiSprites.push_back(m_gemUiSprite);

	m_coinUiSprite = std::make_shared<sf::Sprite>();
	m_coinUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_coin_ui.png")));
	m_coinUiSprite->setPosition(sf::Vector2f(m_screenCenter.x + 60.f, 50.f));
	m_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
	m_uiSprites.push_back(m_coinUiSprite);

	// Key pickup sprite.
	m_keyUiSprite = std::make_shared<sf::Sprite>();
	m_keyUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_key_ui.png")));
	m_keyUiSprite->setPosition(sf::Vector2f(m_screenSize.x - 120.f, m_screenSize.y - 70.f));
	m_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
	m_uiSprites.push_back(m_keyUiSprite);

	// Load stats.
    m_accuracyStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_accuracy_ui.png");
    m_accuracyStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_accuracy_ui_alt.png");
    
    m_accuracyStatSprite = std::make_shared<sf::Sprite>();
    m_accuracyStatSprite->setTexture(TextureManager::GetTexture(m_accuracyStatTextureIDs[0]));
    m_accuracyStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
    m_accuracyStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 390.f, m_screenSize.y - 30.f));
    m_uiSprites.push_back(m_accuracyStatSprite);
    
	m_attackStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_attack_ui.png");
	m_attackStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_attack_ui_alt.png");

	m_attackStatSprite = std::make_shared<sf::Sprite>();
	m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[0]));
	m_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_attackStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 270.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_attackStatSprite);

	m_defenseStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_defense_ui.png");
	m_defenseStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_defense_ui_alt.png");

	m_defenseStatSprite = std::make_shared<sf::Sprite>();
	m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[0]));
	m_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_defenseStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 150.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_defenseStatSprite);

	m_strengthStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_strength_ui.png");
	m_strengthStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_strength_ui_alt.png");

	m_strengthStatSprite = std::make_shared<sf::Sprite>();
	m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[0]));
	m_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
	m_strengthStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 30.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_strengthStatSprite);

	m_dexterityStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_dexterity_ui.png");
	m_dexterityStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_dexterity_ui_alt.png");

	m_dexterityStatSprite = std::make_shared<sf::Sprite>();
	m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[0]));
	m_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_dexterityStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 90.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_dexterityStatSprite);

	m_staminaStatTextureIDs[0] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_stamina_ui.png");
	m_staminaStatTextureIDs[1] = TextureManager::AddTexture(resourcePath() + "/resources/ui/spr_stamina_ui_alt.png");

	m_staminaStatSprite = std::make_shared<sf::Sprite>();
	m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[0]));
	m_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_staminaStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 210.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_staminaStatSprite);
    
    // Show which stats have been boosted by traits
    auto traits = m_player.GetPlayerTraits();
    for (PLAYER_TRAIT trait : *traits)
    {
        switch(trait)
        {
            case PLAYER_TRAIT::ATTACK:
                m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[1]));
                m_attackStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::DEFENSE:
                m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[1]));
                m_defenseStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::STRENGTH:
                m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[1]));
                m_strengthStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::DEXTERITY:
                m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[1]));
                m_dexterityStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::STAMINA:
                m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[1]));
                m_staminaStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::ACCURACY:
                m_accuracyStatSprite->setTexture(TextureManager::GetTexture(m_accuracyStatTextureIDs[1]));
                m_accuracyStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            case PLAYER_TRAIT::COUNT:
                // errors!
                break;
        }
    }
    // Scale UI sprites according to the UI_SCALE factor
    for(auto sprite : m_uiSprites)
    {
        sprite->setScale(UI_SCALE, UI_SCALE);
    }
}

// Load a level from file
void Game::LoadLevel()
{
    // Load the level.
    m_level.LoadLevelFromFile(resourcePath() + "/resources/data/level_data.txt");
    
    // Set the level color
    m_level.SetColor(sf::Color::Green);
    
    // Set the position of the player
    // Randomise the starting location
    std::vector<sf::Vector2f> startLocations;
    startLocations.push_back(sf::Vector2f(552,593));
    startLocations.push_back(sf::Vector2f(1043,750));
    startLocations.push_back(sf::Vector2f(328,766));
    
    m_player.GetComponent<TransformComponent>()->SetPosition(startLocations[std::rand() % startLocations.size()]);
    
    // Populate level.
    PopulateLevel();
    
    // change some tiles to a random tile type
    SpawnRandomTiles(TILE::FLOOR_ALT, std::rand() % MAX_TILE_SPAWN_COUNT);
}

// Generates a random level
void Game::GenerateLevel()
{
    // Create a config to pass into the level
    LevelConfig config;
    config.dimentions.x = std::rand() % 15 + 5;
    config.dimentions.y = std::rand() % 15 + 5;
    
    if(config.dimentions.x % 2 == 0)
        config.dimentions.x += 1;
    
    if(config.dimentions.y % 2 == 0)
        config.dimentions.y += 1;
    
    config.roomCount = static_cast<int>((config.dimentions.x * config.dimentions.y) / 25);
    
    // Randomly select level generator to use
    LEVEL_GENERATOR generatorType = static_cast<LEVEL_GENERATOR>(std::rand() % 2);
    
    std::shared_ptr<LevelGenerator> generator;
    
    switch(generatorType)
    {
        case LEVEL_GENERATOR::BACKTRACKER:
            generator = std::make_shared<BacktrackerLevelGenerator>();
            break;
        case LEVEL_GENERATOR::OPEN_ROOM:
            generator = std::make_shared<OpenRoomLevelGenerator>();
            break;
        case LEVEL_GENERATOR::COUNT:
            // error!
            break;
    }
    
    // Crete new level
    m_level.GenerateLevel(config, generator);
    
    // Throw down some darkness
    ConstructLightGrid();
    
    // Place key randomly in level
    SpawnItem(ITEM::KEY);
    
    // Throw some items in the level
    PopulateLevel();
    
    // change some tiles to an alt floor tile
    int levelArea = m_level.GetSize().x * m_level.GetSize().y;
    SpawnRandomTiles(TILE::FLOOR_ALT, std::rand() % (levelArea/25));
    
    // Randomise the generation of a level goal
    if((std::rand() % 3) == 0 && !m_hasActiveGoal)
    {
        GenerateLevelGoal();
    }
    
    m_player.GetComponent<TransformComponent>()->SetPosition(m_level.GetSpawnLocation());
}

// Populate the level with items.
void Game::PopulateLevel()
{
    // Spawn enemies and items based on the size of the level
    sf::Vector2u levelSize = m_level.GetSize();
    int levelArea = levelSize.x * levelSize.y;
    
    int itemSpawnCount = levelArea/7;
    int enemySpawncount = levelArea/18;
    //int enemySpawncount = 1;
    
    // Create items
    for(int i=0; i<itemSpawnCount; i++)
    {
        // randomise which items spawn on level load
        if(std::rand() % 2)
        {
            // Choose random item to spawn
            // Don't randomly spawn other keys
            ITEM itemType = static_cast<ITEM>(std::rand() % (static_cast<int>(ITEM::COUNT)-1));
            SpawnItem(itemType);
        }
    }
    
    // Create enemies
    for(int i=0; i<enemySpawncount; i++)
    {
        if(std::rand() %2)
        {
            // randomly choose an enemy type to generate
            ENEMY enemyType = static_cast<ENEMY>(std::rand() % static_cast<int>(ENEMY::COUNT));
            SpawnEnemy(enemyType);
        }
    }
}

void Game::SpawnItem(ITEM itemType, sf::Vector2f position)
{
    // Spawn location of the item
    sf::Vector2f spawnLocation;
    
    if(position.x >= 0 && position.y >= 0)
    {
        spawnLocation = position;
    }
    else
    {
        spawnLocation = m_level.GetRandomSpawnLocation();
    }
    
    // Create the item object
    std::unique_ptr<Item> item = nullptr;
    
    switch(itemType)
    {
        case ITEM::GEM:
            item = std::make_unique<Gem>();
            break;
        case ITEM::GOLD:
            item = std::make_unique<Gold>();
            break;
        case ITEM::HEART:
            item = std::make_unique<Heart>();
            break;
        case ITEM::POTION:
            item = std::make_unique<Potion>();
            break;
        case ITEM::KEY:
            item = std::make_unique<Key>();
            break;
        case ITEM::POISON_HEART:
            item = std::make_unique<PoisonHeart>();
            break;
        case ITEM::COUNT:
            // shouldn't be doing this...
            break;
            
    }
    
    if(item != nullptr)
    {
        item->GetComponent<TransformComponent>()->SetPosition(spawnLocation);
        m_items.push_back(std::move(item));
    }
}

void Game::GenerateLevelGoal()
{
    std::ostringstream ss;
    
    // Reset goal variables
    m_killGoal = 0;
    m_gemGoal = 0;
    m_goldGoal = 0;
    
    int goalType = std::rand() % 3;
    
    switch(goalType)
    {
        case 0:  // Enemies
            m_killGoal = std::rand() % 6 + 5;
            ss << "Current goal: Kill " << m_killGoal << " enemies!" << std::endl;
            break;
            
        case 1:  // Gold
            m_goldGoal = std::rand() % 51 + 50;
            ss << "Current goal: Collect " << m_goldGoal << " gold!" << std::endl;
            break;
            
        case 2:  // Gems
            m_gemGoal = std::rand() % 6 + 5;
            ss << "Current goal: Collect " << m_gemGoal << " gems!" << std::endl;
            break;
            
        default:
            // error!
            break;
    }
    
    m_hasActiveGoal = true;
    m_goalString = ss.str();
}

void Game::SpawnEnemy(ENEMY enemyType, sf::Vector2f position)
{
    // Spawn location of enemy
    sf::Vector2f spawnLocation;
    
    if(position.x >= 0 && position.y >= 0)
    {
        spawnLocation = position;
    }
    else
    {
        // Don't spawn enemies ontop of the player
        // This will possibly break the game on small maps...
        while(true)
        {
            spawnLocation = m_level.GetRandomSpawnLocation();
            if(DistanceBetweenPoints(spawnLocation, m_level.GetSpawnLocation()) > 200.f)
                break;
        }
    }
    
    // Create the enemy object
    std::unique_ptr<Enemy> enemy = nullptr;
    switch (enemyType)
    {
        case ENEMY::SLIME:
            enemy = std::make_unique<Slime>();
            break;
        case ENEMY::HUMANOID:
            enemy = std::make_unique<Humanoid>();
            break;
        case ENEMY::COUNT:
            // error..
            break;
    }
    
    // make sure an enemy was actually created
    if(enemy != nullptr)
    {
        enemy->GetComponent<TransformComponent>()->SetPosition(spawnLocation);
        m_enemies.push_back(std::move(enemy));
    }
}

// Spawn tiles in random spots
void Game::SpawnRandomTiles(TILE tileType, int count)
{
    for(int i=0; i<count; i++)
    {
        int rowIndex(0);
        int columnIndex(0);
        
        while(!m_level.IsSpawnableFloor(columnIndex, rowIndex))
        {
            columnIndex = std::rand() % m_level.GetSize().x;
            rowIndex = std::rand() & m_level.GetSize().y;
        }
        m_level.SetTile(columnIndex, rowIndex, tileType);
    }
    
}

// play a sound
void Game::PlaySound(sf::Sound& sound, sf::Vector2f position)
{
    float pitch = ((std::rand() % 11) + 95)/100;
    //sound.setPitch(pitch);
    sound.setPosition(position.x, position.y, 0);
    sound.play();
}

// Returns the running state of the game.
bool Game::IsRunning()
{
	return m_isRunning;
}

// Main game loop.
void Game::Run()
{
	float currentTime = m_timestepClock.restart().asSeconds();
	float timeDelta = 0.f;

	// Loop until there is a quite message from the window or the user pressed escape.
	while (m_isRunning)
	{
		// Check if the game was closed.
		sf::Event event;
		if (m_window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
			{
				m_window.close();
				return;
			}
		}

		float newTime = m_timestepClock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		// Update all items in the level.
		if (!m_levelWasGenerated)
		{
			Update(frameTime);

			// Draw all items in the level.
			Draw(frameTime);
		}
		else
		{
			m_levelWasGenerated = false;
		}
	}

	// Shut the game down.
	m_window.close();
}

// Updates the game.
void Game::Update(float timeDelta)
{
	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Main menu code ...
		break;

	case GAME_STATE::PLAYING:
	{
		// First check if the player is at the exit. If so there's no need to update anything.
		Tile* playerCurrentTile = m_level.GetTile(m_player.GetComponent<TransformComponent>()->GetPosition());
        

		if (playerCurrentTile->type == TILE::WALL_DOOR_UNLOCKED ||
            playerCurrentTile->type == TILE::WALL_DOOR_UNLOCKED_RIGHT)
		{
			// clear current items
            m_items.clear();
            
            // clear enemies
            m_enemies.clear();
            
            // create new level
            GenerateLevel();
            
            // Set the key as not collected.
            m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
		}
		else
		{
			// Update the player.
			m_player.Update(timeDelta, m_level);
            
            // Check if player has moved tiles
            if(playerCurrentTile != m_playerPreviousTile)
            {
                // Store new location
                m_playerPreviousTile = playerCurrentTile;
                
                // Update the pathing of all enemies in range of player
                for(const auto& enemy : m_enemies)
                {
                    if(DistanceBetweenPoints(m_player.GetComponent<TransformComponent>()->GetPosition(), enemy->GetComponent<TransformComponent>()->GetPosition()) < 300.f)
                    {
                        enemy->UpdatePathfinding(m_level, m_player.GetComponent<TransformComponent>()->GetPosition());
                    }
                }
            }

			// Store the player position as it's used many times.
			sf::Vector2f playerPosition = m_player.GetComponent<TransformComponent>()->GetPosition();

			// If the player is attacking create a projectile.
			if (m_player.IsAttacking())
			{
				if (m_player.GetMana() >= 2)
				{
					sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
					
                    std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::GetTexture(m_projectileTextureID), playerPosition, m_screenCenter, target);
					m_playerProjectiles.push_back(std::move(proj));

					// Reduce player mana.
					m_player.SetMana(m_player.GetMana() - 2);
				}
			}

			// Update all items.
			UpdateItems(playerPosition);

			// Update level light.
			UpdateLight(playerPosition);

			// Update all enemies.
			UpdateEnemies(playerPosition, timeDelta);

			// Update all projectiles.
			UpdateProjectiles(timeDelta);
            
            // Find torch closest to the player.
            auto torches = m_level.GetTorches();
            
            if(!torches->empty())
            {
                sf::Vector2f closestTorch = torches->front()->GetComponent<TransformComponent>()->GetPosition();
                float minDistance = DistanceBetweenPoints(playerPosition, closestTorch);
                for(auto torch : *torches)
                {
                    // While we are looping through them all, call update too
                    torch->Update(timeDelta);
                    
                    float distance = DistanceBetweenPoints(playerPosition, torch->GetComponent<TransformComponent>()->GetPosition());
                    if(distance < minDistance)
                    {
                        closestTorch = torch->GetComponent<TransformComponent>()->GetPosition();
                        minDistance = distance;
                    }
                }
                
                // move the fire sound to the closest torch
                m_fireSound.setPosition(closestTorch.x, closestTorch.y, 0);
            }
            
            // Update the listener position
            sf::Listener::setPosition(playerPosition.x, playerPosition.y, 0.f);

			// Center the view.
			m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
		}
        
        if(m_hasActiveGoal)
        {
            if(m_gemGoal <= 0 && m_goldGoal <= 0 && m_killGoal <= 0)
            {
                m_scoreTotal += std::rand() % 1001 + 1000;
                m_hasActiveGoal = false;
            }
            else{
                std::ostringstream ss;
                
                if (m_goldGoal > 0)
                    ss << "Current Goal: Collect " << m_goldGoal << "gold" << "!" << std::endl;
                
                else if (m_gemGoal > 0)
                    ss << "Current Goal: Collect " << m_gemGoal << " gem" << "!" << std::endl;
                
                else if (m_killGoal > 0)
                    ss << "Current Goal: Kill " << m_killGoal << " enemies" << "!" << std::endl;

                m_goalString = ss.str();
            }
        }
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Game over code
		break;
	}
}

// Updates the level light.
void Game::UpdateLight(sf::Vector2f playerPosition)
{
	for (sf::Sprite& sprite : m_lightGrid)
	{
		float tileAlpha = 255.f;			// Tile alpha.
		float distance = 0.f;				// The distance between player and tile.

		// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), playerPosition);

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}

		// Get all torches from the level.
		auto torches = m_level.GetTorches();

		// If there are torches.
		if (!torches->empty())
		{
			// Update the light surrounding each torch.
			for (std::shared_ptr<Torch> torch : *torches)
			{
                // The torch position refers to the the top left corner of the sprite
                // Need to make the distance calculation from the center of the sprite so the
                // light gets centered around the torch correctly
                sf::Vector2f torchCenter = torch->GetComponent<TransformComponent>()->GetPosition();
                torchCenter.x -= 12.5;
                torchCenter.y -= 12.5;
                
				// If the light tile is within range of the torch.
                distance = DistanceBetweenPoints(sprite.getPosition(), torchCenter);
				if (distance < 100.f)
				{
					// Edit its alpha.
					tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * torch->GetBrightness();
				}
			}

			// Ensure alpha does not go negative.
			if (tileAlpha < 0)
			{
				tileAlpha = 0;
			}
		}

		// Set the sprite transparency.
		sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
	}
}

// Updates all items in the level.
void Game::UpdateItems(sf::Vector2f playerPosition)
{
	// Update all items.
	auto itemIterator = m_items.begin();
	while (itemIterator != m_items.end())
	{
		// Get the item from the iterator.
		Item& item = **itemIterator;

		// Check if the player is within pickup range of the item.
		if (DistanceBetweenPoints(item.GetComponent<TransformComponent>()->GetPosition(), playerPosition) < 40.f)
		{
			// Check what type of object it was.
			switch (item.GetType())
			{
                case ITEM::GOLD:
                {
                    // Get the amount of gold.
                    int goldValue = dynamic_cast<Gold&>(item).GetGoldValue();

                    // Add to the gold total.
                    m_goldTotal += goldValue;
                    
                    // Check if active level goal
                    if(m_hasActiveGoal)
                    {
                        m_goldGoal -= goldValue;
                    }
                    
                    // Play coin pickup sound
                    m_audio.PlaySound(SOUND_ID::COIN_PICKUP);
                }
                break;

                case ITEM::GEM:
                {
                    // Get the score of the gem.
                    int scoreValue = dynamic_cast<Gem&>(item).GetScoreValue();

                    // Add to the score total
                    m_scoreTotal += scoreValue;
                    
                    // Check if active level goal
                    if(m_hasActiveGoal)
                    {
                        m_gemGoal -= 1;
                    }
                    
                    // Play gem pickup sound.
                    m_audio.PlaySound(SOUND_ID::GEM_PICKUP);
                }
                break;

                case ITEM::KEY:
                {
                    // Unlock the door.
                    m_level.UnlockDoor();

                    // Set the key as collected.
                    m_keyUiSprite->setColor(sf::Color::White);

                    m_audio.PlaySound(SOUND_ID::KEY_PICKUP);
                }
                break;

                case ITEM::POTION:
                {
                    Potion& potion = dynamic_cast<Potion&>(item);
                    POTION potionType = potion.GetPotionType();
                    
                    switch(potionType)
                    {
                        case POTION::ATTACK:
                            m_player.SetAttack(m_player.GetAttack() + potion.GetAttack());
                            break;
                        case POTION::DEFENSE:
                            m_player.SetDefense(m_player.GetDefense() + potion.GetDefense());
                            break;
                        case POTION::DEXTERITY:
                            m_player.SetDexterity(m_player.GetDexterity() + potion.GetDexterity());
                            break;
                        case POTION::STAMINA:
                            m_player.SetStamina(m_player.GetStamina() + potion.GetStamina());
                            break;
                        case POTION::STRENGTH:
                            m_player.SetStrength(m_player.GetStrength() + potion.GetStrength());
                            break;
                        case POTION::ACCURACY:
                            m_player.SetAccuracy(m_player.GetAccuracy() + potion.GetAccuracy());
                            break;
                        case POTION::COUNT:
                            // error!
                            break;
                    }
                    
                }
                break;

                case ITEM::HEART:
                {
                    // Cast to heart and get health.
                    Heart& heart = dynamic_cast<Heart&>(item);

                    m_player.SetHealth(m_player.GetHealth() + heart.GetHealth());
                }
                break;
                case ITEM::POISON_HEART:
                {
                    // Cast to heart and get health.
                    PoisonHeart& poisonHeart = dynamic_cast<PoisonHeart&>(item);
                    
                    m_player.SetHealth(m_player.GetHealth() + poisonHeart.GetHealth());
                }
                break;
                    
                case ITEM::COUNT:
                {}
                break;
			}
            

			// Finally, delete the object.
			itemIterator = m_items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}

// Updates all enemies in the level.
void Game::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = m_level.GetTile(m_player.GetComponent<TransformComponent>()->GetPosition());

	auto enemyIterator = m_enemies.begin();
	while (enemyIterator != m_enemies.end())
	{
		// Create a bool so we can check if an enemy was deleted.
		bool enemyWasDeleted = false;

		// Get the enemy object from the iterator.
		Enemy& enemy = **enemyIterator;

		// Get the tile that the enemy is on.
		Tile* enemyTile = m_level.GetTile(enemy.GetComponent<TransformComponent>()->GetPosition());

		// Check for collisions with projectiles.
		auto projectilesIterator = m_playerProjectiles.begin();
		while (projectilesIterator != m_playerProjectiles.end())
		{
			// Get the projectile object from the iterator.
			Projectile& projectile = **projectilesIterator;

			// If the enemy and projectile occupy the same tile they have collided.
			if (enemyTile == m_level.GetTile(projectile.GetComponent<TransformComponent>()->GetPosition()))
			{
				// Delete the projectile.
				projectilesIterator = m_playerProjectiles.erase(projectilesIterator);

                // calculate how much damage to deal
                int damage = 10;
                damage += m_player.GetStrength() + m_player.GetAttack() - enemy.GetDefense();
				
                // Damage the enemy.
                enemy.Damage(damage);

				// If the enemy is dead remove it.
				if (enemy.IsDead())
				{
					// Get the enemy position.
					sf::Vector2f position = enemy.GetComponent<TransformComponent>()->GetPosition();

					// Spawn loot.
					for (int i = 0; i < 5; i++)
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;

						switch (std::rand() % 2)
						{
						case 0: // Spawn gold.
                            SpawnItem(ITEM::GOLD, position);
							break;

						case 1: // Spawn gem.
							SpawnItem(ITEM::GEM, position);
							break;
						}

					}

					if ((std::rand() % 5) == 0)			// 1 in 5 change of spawning health.
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
                        SpawnItem(ITEM::HEART, position);
					}
					// 1 in 5 change of spawning potion.
					else if ((std::rand() % 5) == 1)
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
                        SpawnItem(ITEM::POTION, position);
					}
                    
                    // Play enemy killed sound
                    PlaySound(m_enemyDieSound, position);

					// Delete enemy.
					enemyIterator = m_enemies.erase(enemyIterator);
					enemyWasDeleted = true;

					// Since the enemy is dead we no longer need to check projectiles.
					projectilesIterator = m_playerProjectiles.end();
                    
                    // After the enemy has died check level goal
                    if(m_hasActiveGoal)
                    {
                        m_killGoal -= 1;
                    }
				}
			}
			else
			{
				// Move to the next projectile.
				++projectilesIterator;
			}
		}

		// If the enemy was not deleted, update it and increment the iterator.
		if (!enemyWasDeleted)
		{
			enemy.Update(timeDelta);
			++enemyIterator;
		}

		// Check for collision with player.
		if (enemyTile == playerTile)
		{
			if (m_player.CanTakeDamage())
			{
                int damage = 5 + enemy.GetAttack() + enemy.GetStrength() - m_player.GetDefense();
                m_player.Damage(std::max(damage, 2));
                
                m_audio.PlaySound(SOUND_ID::PLAYER_HIT);
			}
		}
	}
}

// Updates all projectiles in the level.
void Game::UpdateProjectiles(float timeDelta)
{
	auto projectileIterator = m_playerProjectiles.begin();
	while (projectileIterator != m_playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Projectile& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		TILE projectileTileType = m_level.GetTile(projectile.GetComponent<TransformComponent>()->GetPosition())->type;

		// If the tile the projectile is on is not floor, delete it.
		if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
		{
			projectileIterator = m_playerProjectiles.erase(projectileIterator);
		}
		else
		{
			// Update the projectile and move to the next one.
			projectile.Update(timeDelta);
			++projectileIterator;
		}
	}
}

// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
    return (std::abs(std::sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}

// Draw the given string at the given position.
void Game::DrawString(std::string text, sf::Vector2f position, unsigned int size)
{
	// Clear the old data.
	m_stringStream.str(std::string());
	m_string.clear();

	m_stringStream << text;
	m_string = m_stringStream.str();
    
    // Scale the text according to the UI scale
    int scaledSize = size * UI_SCALE;

	m_text.setString(m_string);
	m_text.setFont(m_font);
	m_text.setCharacterSize(scaledSize);
	m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

	m_window.draw(m_text);
}

// Draw the current game scene.
void Game::Draw(float timeDelta)
{
	// Clear the screen.
	m_window.clear(sf::Color(3, 3, 3, 225));		// Gray

	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Draw main menu ...
		break;

	case GAME_STATE::PLAYING:
	{
		// Set the main game view.
		m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

		// Draw the level.
		m_level.Draw(m_window, timeDelta);

		// Draw all objects.
		for (const auto& item : m_items)
		{
            item->GetComponent<SpriteComponent>()->Draw(m_window, timeDelta);
            
            // if the object has text, render that too
            std::shared_ptr<TextComponent> textComponent = item->GetComponent<TextComponent>();
            
            if(textComponent != nullptr)
                textComponent->Draw(m_window, timeDelta);
		}

		// Draw all enemies.
		for (const auto& enemy : m_enemies)
		{
            enemy->GetComponent<SpriteComponent>()->Draw(m_window, timeDelta);
		}

		// Draw all projectiles
		for (const auto& proj : m_playerProjectiles)
		{
            proj->GetComponent<SpriteComponent>()->Draw(m_window, timeDelta);
		}

		// Draw the player.
        m_player.GetComponent<SpriteComponent>()->Draw(m_window, timeDelta);

		// Draw level light.
		for (const sf::Sprite& sprite : m_lightGrid)
		{
			m_window.draw(sprite);
		}

		// Switch to UI view.
		m_window.setView(m_views[static_cast<int>(VIEW::UI)]);

		// Draw player aim.
		m_window.draw(m_player.GetAimSprite());

		// Draw player stats.
		DrawString(std::to_string(m_player.GetAccuracy()), sf::Vector2f(m_screenCenter.x - 330.f, m_screenSize.y - 30.f), 25);
        DrawString(std::to_string(m_player.GetAttack()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetDefense()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetStrength()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetDexterity()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetStamina()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);

		// Draw player score.
		std::string scoreString;

		if (m_scoreTotal > 99999)
		{
			scoreString = std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9999)
		{
			scoreString = "0" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 999)
		{
			scoreString = "00" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 99)
		{
			scoreString = "000" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9)
		{
			scoreString = "0000" + std::to_string(m_scoreTotal);
		}
		else
		{
			scoreString = "00000" + std::to_string(m_scoreTotal);
		}

		DrawString(scoreString, sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);

		// Draw gold total.
		std::string goldString;

		if (m_goldTotal > 99999)
		{
			goldString = std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9999)
		{
			goldString = "0" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 999)
		{
			goldString = "00" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 99)
		{
			goldString = "000" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9)
		{
			goldString = "0000" + std::to_string(m_goldTotal);
		}
		else
		{
			goldString = "00000" + std::to_string(m_goldTotal);
		}

		DrawString(goldString, sf::Vector2f(m_screenCenter.x + 220.f, 40.f), 40);

        // Draw current goal
        if(m_hasActiveGoal)
        {
            DrawString(m_goalString, sf::Vector2f(m_window.getSize().x /2, m_window.getSize().y - (75 * UI_SCALE)), 30);
        }
        
        // Draw rest of the UI.
		for (const auto& sprite : m_uiSprites)
		{
			m_window.draw(*sprite);
		}

		// Draw the current room and floor.
		DrawString("Floor " + std::to_string(m_level.GetFloorNumber()), sf::Vector2f(70.f, m_screenSize.y - 65.f), 25);
		DrawString("Level " + std::to_string(m_level.GetLevelNumber()), sf::Vector2f(70.f, m_screenSize.y - 30.f), 25);

		// Draw health and mana bars.
		m_healthBarSprite->setTextureRect(sf::IntRect(0, 0, ((213.f / m_player.GetMaxHealth()) * m_player.GetHealth()) * UI_SCALE, 8));
		m_window.draw(*m_healthBarSprite);

		m_manaBarSprite->setTextureRect(sf::IntRect(0, 0, ((213.f / m_player.GetMaxMana()) * m_player.GetMana()) * UI_SCALE, 8));
		m_window.draw(*m_manaBarSprite);
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Draw game over screen ...
		break;
	}

	// Present the back-buffer to the screen.
	m_window.display();
}
