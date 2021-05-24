#include "PCH.hpp"
#include "Level.hpp"
#include "ResourcePath.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

#include "LevelGenerator.hpp"
#include "BacktrackerLevelGenerator.hpp"
#include "OpenRoomLevelGenerator.hpp"

#include <iostream>

// Constructor.
Level::Level() :
m_floorNumber(1),
m_levelNumber(0)
{
	// Load all tiles.
	AddTile(resourcePath() + "resources/tiles/spr_tile_floor.png", TILE::FLOOR);
    AddTile(resourcePath() + "resources/tiles/spr_tile_floor_alt.png", TILE::FLOOR_ALT);
    AddTile(resourcePath() + "resources/tiles/spr_tile_floor_spikes.png", TILE::FLOOR_SPIKES);

	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_top.png", TILE::WALL_TOP);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_top_left.png", TILE::WALL_TOP_LEFT);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_top_right.png", TILE::WALL_TOP_RIGHT);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_top_t.png", TILE::WALL_TOP_T);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_top_end.png", TILE::WALL_TOP_END);

	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_bottom_t.png", TILE::WALL_BOTTOM_T);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_bottom_end.png", TILE::WALL_BOTTOM_END);

	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_side.png", TILE::WALL_SIDE);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);

	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_intersection.png", TILE::WALL_INTERSECTION);
	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_single.png", TILE::WALL_SINGLE);

	AddTile(resourcePath() + "resources/tiles/spr_tile_wall_entrance.png", TILE::WALL_ENTRANCE);
	AddTile(resourcePath() + "resources/tiles/spr_tile_door_locked.png", TILE::WALL_DOOR_LOCKED);
	AddTile(resourcePath() + "resources/tiles/spr_tile_door_unlocked.png", TILE::WALL_DOOR_UNLOCKED);
    
    AddTile(resourcePath() + "resources/tiles/spr_tile_wall_entrance_left.png", TILE::WALL_ENTRANCE_LEFT);
    AddTile(resourcePath() + "resources/tiles/spr_tile_door_locked_right.png", TILE::WALL_DOOR_LOCKED_RIGHT);
    AddTile(resourcePath() + "resources/tiles/spr_tile_door_unlocked_right.png", TILE::WALL_DOOR_UNLOCKED_RIGHT);
}

// Sets overlay color of level tiles
void Level::SetColor(sf::Color tileColor)
{
    for(int i=0; i<m_grid.GetDimentions().x; i++)
    {
        for(int j=0; j<m_grid.GetDimentions().y; j++)
        {
            m_grid[i][j].sprite.setColor(tileColor);
        }
    }
}

// Create and adds a tile sprite to the list of those available.
int Level::AddTile(std::string fileName, TILE tileType)
{
	// Add the texture to the texture manager.
	int textureID = TextureManager::AddTexture(fileName);

	if (textureID < 0)
	{
		return -1; // Failed
	}
	else
	{
		m_textureIDs[static_cast<int>(tileType)] = textureID;
	}

	// Return the ID of the tile.
	return textureID;
}

// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, TILE tileType)
{
	// Check that the provided tile index is valid.
	if ((columnIndex >= m_grid.GetDimentions().x) || (rowIndex >= m_grid.GetDimentions().y))
	{
		return;
	}

	// check that the sprite index is valid
	if (tileType >= TILE::COUNT)
	{
		return;
	}

	// change that tiles sprite to the new index
	m_grid[columnIndex][rowIndex].type = tileType;
	m_grid[columnIndex][rowIndex].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(tileType)]));
}

// Returns world coordinates of a tile
sf::Vector2f Level::GetActualTileLocation(int columnIndex, int rowIndex)
{
    sf::Vector2f location;
    
    location.x = (columnIndex * TILE_SIZE) + (TILE_SIZE / 2);
    location.y = (rowIndex * TILE_SIZE) + (TILE_SIZE / 2);
    
    return location;
}

// Returns a valid spawn location
sf::Vector2f Level::GetRandomSpawnLocation()
{
    int rowIndex(0);
    int columnIndex(0);
    
    // Loop until a location is found
    while (!IsSpawnableFloor(columnIndex, rowIndex))
    {
        columnIndex = rand() % m_grid.GetDimentions().x;
        rowIndex = rand() % m_grid.GetDimentions().y;
    }
    
    sf::Vector2f tileLocation = GetActualTileLocation(columnIndex, rowIndex);
    
    // add some random offset on the tile
    tileLocation.x += std::rand() % 21 - 10;
    tileLocation.y += std::rand() % 21 - 10;
    
    return tileLocation;
}

// Gets the current floor number.
int Level::GetFloorNumber() const
{
	return m_floorNumber;
}

// Gets the current room number.
int Level::GetLevelNumber() const
{
	return m_levelNumber;
}

// Get the spawn location coords
sf::Vector2f Level::GetSpawnLocation()
{
    return GetActualTileLocation(m_grid.GetSpawnPosition().x, m_grid.GetSpawnPosition().y);
}

// Gets the size of the level in terms of tiles.
sf::Vector2u Level::GetSize() const
{
	return m_grid.GetDimentions();
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position)
{
	// Convert to a tile position.
	int tileColumn, tileRow;

	tileColumn = static_cast<int>(position.x) / TILE_SIZE;
	tileRow = static_cast<int>(position.y) / TILE_SIZE;

	return &m_grid[tileColumn][tileRow];
}

// Returns a pointer to the tile at the given index.
Tile* Level::GetTile(int columnIndex, int rowIndex)
{
    if (m_grid.IsValidTile(sf::Vector2u(columnIndex, rowIndex)))
	{
		return &m_grid[columnIndex][rowIndex];
	}
	else
	{
		return nullptr;
	}
}

// Generate the level using input configuration
bool Level::GenerateLevel(LevelConfig& config, std::shared_ptr<LevelGenerator> generator)
{
    //BacktrackerLevelGenerator generator;
    //OpenRoomLevelGenerator generator;
    
    // Create the level grid
    generator->GenerateLevel(m_grid, config);
    
    // Apply textures to the level
    SetTextures();
    
    // Set color of the level
    // Change color every 5 rooms
    m_levelNumber++;
    
    if(m_levelNumber >= 5)
    {
        m_levelNumber = 0;
        m_floorNumber++;
        
        sf::Uint8 red = std::rand() %101 + 100;
        sf::Uint8 green = std::rand() %101 + 100;
        sf::Uint8 blue = std::rand() %101 + 100;
        
        SetColor(sf::Color(red, green, blue, 255));
    }
    
    // Generate torches based on level size
    m_torches.clear();
    int torchCount = static_cast<int>((m_grid.GetDimentions().x * m_grid.GetDimentions().y) / 45);
    CreateTorches(torchCount);
    
    return true;
}

// Generate a random level
bool Level::GenerateLevel()
{
    LevelConfig config;
    config.dimentions.x = std::rand() % 15 + 5;
    config.dimentions.y = std::rand() % 15 + 5;
    
    if(config.dimentions.x % 2 == 0)
        config.dimentions.x += 1;
    
    if(config.dimentions.y % 2 == 0)
        config.dimentions.y += 1;
    
    config.roomCount = static_cast<int>((config.dimentions.x * config.dimentions.y) / 25);
    
    std::shared_ptr<LevelGenerator> generator = std::make_shared<BacktrackerLevelGenerator>();
    
    return GenerateLevel(config,generator);
}

// Create torches for the level
void Level::CreateTorches(int torchCount)
{
    // Clear previously generated torches
    m_torches.clear();
    
    int spawnedCount = 0;
    // simples way to start.. Just randomly pick tiles until a wall is selected
    while(spawnedCount < torchCount)
    {
        int x = std::rand() % m_grid.GetDimentions().x;
        int y = std::rand() % m_grid.GetDimentions().y;
        
        if(m_grid.IsWall(sf::Vector2u(x, y)))
        {
            std::shared_ptr<Torch> torch = std::make_shared<Torch>();
            torch->GetComponent<TransformComponent>()->SetPosition(GetActualTileLocation(x, y));
            m_torches.push_back(torch);
            
            spawnedCount++;
        }
    }
}

// Sets the textures for the level based on tile types
void Level::SetTextures()
{
    for(int i=0; i<m_grid.GetDimentions().x; i++)
    {
        for(int j=0; j<m_grid.GetDimentions().y; j++)
        {
            m_grid[i][j].sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);
            m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(m_grid[i][j].type)]));
        }
    }
}

// Loads a level from a .txt file.
bool Level::LoadLevelFromFile(std::string fileName)
{
    /*
	// Create all the fields we need.
	std::ifstream file(fileName);

	// Read level data into 2D int array that describes the level.
	if (file.is_open())
	{
		for (int j = 0; j < m_gridSize.x; ++j)
		{
			for (int i = 0; i < m_gridSize.y; ++i)
			{
				// Get the cell that we're working on.
				auto& cell = m_grid[i][j];

				// Read the character. Out of 4 characters we only want 2nd and 3rd.
				std::string input;

				file.get();
				input += file.get();
				input += file.get();
				file.get();

				// Convert string to int.
				std::stringstream convert(input);
				int tileID;
				convert >> tileID;

				// Set type, sprite and position.
				cell.type = static_cast<TILE>(tileID);
                
				cell.sprite.setTexture(TextureManager::GetTexture(m_textureIDs[tileID]));
                cell.sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);

				// Check for entry/exit nodes.
				if (cell.type == TILE::WALL_DOOR_LOCKED)
				{
					// Save the location of the exit door.
					m_doorTileIndices = sf::Vector2i(i, 0);
				}
			}

			// Read end line char.
            for (;;)
            {
                int c = file.peek();
                if (c != '\n' && c != '\r')
                {
                    break;
                }
                file.get();
            }
		}

		file.close(); //closing the file

		// Create torches at specific locations.
        std::vector<sf::Vector2f> torchLocations;

        torchLocations.push_back(GetActualTileLocation(3, 9));
        torchLocations.push_back(GetActualTileLocation(7, 7));
        torchLocations.push_back(GetActualTileLocation(11,11));
        torchLocations.push_back(GetActualTileLocation(13, 15));
        torchLocations.push_back(GetActualTileLocation(15, 3));
        
        // Spawn torches
        for(auto location : torchLocations)
        {
            std::shared_ptr<Torch> torch = std::make_shared<Torch>();
            torch->GetComponent<TransformComponent>()->SetPosition(sf::Vector2f(location.x, location.y));
            m_torches.push_back(torch);
        }
	}
	else
	{
		return false;
	}
     */
	return true;
}

// Unlocks the door in the level.
void Level::UnlockDoor()
{
    TILE exitTile = GetTile(m_grid.GetExitPosition().x, m_grid.GetExitPosition().y)->type;
    
    if(exitTile == TILE::WALL_DOOR_LOCKED || exitTile == TILE::WALL_DOOR_LOCKED_RIGHT)
    {
        // The locked and unlocked doors are next to each other in the enum
        // So adding 1 to the current tile will get the unlocked door
        SetTile(m_grid.GetExitPosition().x, m_grid.GetExitPosition().y, static_cast<TILE>(static_cast<int>(exitTile)+1));
    }
}

// Checks if a given tile is passable
bool Level::IsSolid(int i, int j)
{
    // Check that the tile is valid
    if (m_grid.IsValidTile(sf::Vector2u(i, j)))
    {
        Tile& tile = m_grid[i][j];
        return IsSolid(tile);
    }
    else
        return false;
}

// Checks if a given tile is passable
bool Level::IsSolid(const Tile& tile)
{
    // Check that the tile is valid
    TILE tileType = tile.type;
    return (((tileType != TILE::FLOOR) &&
             (tileType != TILE::FLOOR_ALT)) &&
            (tileType != TILE::WALL_DOOR_UNLOCKED) &&
            (tileType != TILE::WALL_DOOR_UNLOCKED_RIGHT));
}

// Return true if the given tile is floor that can have something spawned on it
bool Level::IsSpawnableFloor(int columnIndex, int rowIndex)
{
	Tile* tile = &m_grid[columnIndex][rowIndex];

    // Spikey floor is not considered 'floor' so items don't spawn on it and it
    // doesn't get spatted by 'alt floor' tiles.
	return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const
{
	return TILE_SIZE;
}

// Reset nodes used for pathfinding
void Level::ResetNodes()
{
    for (int i=0; i<m_grid.GetDimentions().x; i++) {
        for(int j=0; j<m_grid.GetDimentions().y; j++)
        {
            m_grid[i][j].parentNode = nullptr;
            m_grid[i][j].H = 0;
            m_grid[i][j].G = 0;
            m_grid[i][j].F = 0;
        }
    }
}

// Gets a vector of all torches in the level.
std::vector<std::shared_ptr<Torch>>* Level::GetTorches()
{
	return &m_torches;
}

// Draws the level grid to the given render window.
void Level::Draw(sf::RenderWindow& window, float timeDelta)
{
	// Draw the level tiles.
	for (int i = 0; i < m_grid.GetDimentions().x; i++)
	{
		for (int j = 0; j < m_grid.GetDimentions().y; j++)
		{
			window.draw(m_grid[i][j].sprite);
		}
	}

	// Draw all torches.
	for (auto& torch : m_torches)
	{
		torch->GetComponent<SpriteComponent>()->Draw(window, timeDelta);
	}
}
