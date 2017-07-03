#include "PCH.hpp"
#include "Level.hpp"
#include "ResourcePath.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

#include "LevelGeneratorComponent.hpp"

#include <iostream>

// Constructor.
Level::Level() :
m_floorNumber(1),
m_levelNumber(0),
m_doorTileIndices({ 0, 0 }),
m_gridSize(sf::Vector2i(0,0))
{
	// Load all tiles.
	AddTile(resourcePath() + "/resources/tiles/spr_tile_floor.png", TILE::FLOOR);
    AddTile(resourcePath() + "/resources/tiles/spr_tile_floor_alt.png", TILE::FLOOR_ALT);
    AddTile(resourcePath() + "/resources/tiles/spr_tile_floor_spikes.png", TILE::FLOOR_SPIKES);

	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_top.png", TILE::WALL_TOP);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_top_left.png", TILE::WALL_TOP_LEFT);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_top_right.png", TILE::WALL_TOP_RIGHT);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_top_t.png", TILE::WALL_TOP_T);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_top_end.png", TILE::WALL_TOP_END);

	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_bottom_t.png", TILE::WALL_BOTTOM_T);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_bottom_end.png", TILE::WALL_BOTTOM_END);

	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_side.png", TILE::WALL_SIDE);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);

	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_intersection.png", TILE::WALL_INTERSECTION);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_single.png", TILE::WALL_SINGLE);

	AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_entrance.png", TILE::WALL_ENTRANCE);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_door_locked.png", TILE::WALL_DOOR_LOCKED);
	AddTile(resourcePath() + "/resources/tiles/spr_tile_door_unlocked.png", TILE::WALL_DOOR_UNLOCKED);
    
    AddTile(resourcePath() + "/resources/tiles/spr_tile_wall_entrance_left.png", TILE::WALL_ENTRANCE_LEFT);
    AddTile(resourcePath() + "/resources/tiles/spr_tile_door_locked_right.png", TILE::WALL_DOOR_LOCKED_RIGHT);
    AddTile(resourcePath() + "/resources/tiles/spr_tile_door_unlocked_right.png", TILE::WALL_DOOR_UNLOCKED_RIGHT);
}

// Sets overlay color of level tiles
void Level::SetColor(sf::Color tileColor)
{
    for(int i=0; i<m_gridSize.x; i++)
    {
        for(int j=0; j<m_gridSize.y; j++)
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

// Checks if a given tile is passable
bool Level::IsSolid(int i, int j)
{
	// Check that the tile is valid
	if (TileIsValid(i, j))
	{
		int tileIndex = static_cast<int>(m_grid[i][j].type);
		return (((tileIndex != static_cast<int>(TILE::FLOOR)) &&
                 (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) &&
                (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)) &&
                (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED_RIGHT)));
	}
	else
		return false;
}

// Returns the id of the given tile in the 2D level array.
TILE Level::GetTileType(int columnIndex, int rowIndex) const
{
	// Check that the parameters are valid.
	if ((columnIndex >= m_gridSize.x) || (rowIndex >= m_gridSize.y))
	{
		return TILE::EMPTY; // failed
	}

	// Fetch the id.
	return m_grid[columnIndex][rowIndex].type;
}

// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, TILE tileType)
{
	// Check that the provided tile index is valid.
	if ((columnIndex >= m_gridSize.x) || (rowIndex >= m_gridSize.y))
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
    while (!IsFloor(columnIndex, rowIndex))
    {
        columnIndex = rand() % m_gridSize.x;
        rowIndex = rand() % m_gridSize.y;
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

// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row)
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < m_gridSize.x));
	validRow = ((row >= 0) && (row < m_gridSize.y));

	return (validColumn && validRow);
}

// Get the spawn location coords
sf::Vector2f Level::GetSpawnLocation()
{
    return m_spawnLocation;
}

// Gets the size of the level in terms of tiles.
sf::Vector2u Level::GetSize() const
{
	return m_gridSize;
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
	if (TileIsValid(columnIndex, rowIndex))
	{
		return &m_grid[columnIndex][rowIndex];
	}
	else
	{
		return nullptr;
	}
}

bool Level::GenerateLevel(LevelConfig config)
{
    m_gridSize.x = config.dimentions.x;
    m_gridSize.y = config.dimentions.y;
    
    config.roomCount = static_cast<int>((config.dimentions.x * config.dimentions.y) / 25);
    
    LevelGeneratorComponent generator;
    
    generator.GenerateLevel(&m_grid, config);
    
    // Add entry and exit rooms
    GenerateEntryExit();
    
    // Calculate the correct wall type to use after knocking out walls and rooms
    CalculateWalls();
    
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
    int torchCount = static_cast<int>((m_gridSize.x * m_gridSize.y) / 45);
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
    
    return GenerateLevel(config);
}

// Create torches for the level
void Level::CreateTorches(int torchCount)
{
    int spawnedCount = 0;
    // simples way to start.. Just randomly pick tiles until a wall is selected
    while(spawnedCount < torchCount)
    {
        int x = std::rand() % m_gridSize.x;
        int y = std::rand() % m_gridSize.y;
        
        if(IsWall(x, y))
        {
            std::shared_ptr<Torch> torch = std::make_shared<Torch>();
            torch->GetComponent<TransformComponent>()->SetPosition(GetActualTileLocation(x, y));
            m_torches.push_back(torch);
            
            spawnedCount++;
        }
    }
}


// Set the wall textures correctly
void Level::CalculateWalls()
{
    for(int i=0; i<m_gridSize.x; i++)
    {
        for(int j=0; j<m_gridSize.y; j++)
        {
            if(IsWall(i, j))
            {
                // Calculate bit mask
                int value = 0;
                
                TILE type = m_grid[i][j].type;
                
                // Top
                if(IsWall(i,j-1))
                    value += 1;
                
                // Right
                if(IsWall(i+1, j))
                    value += 2;
                
                // Bottom
                if(IsWall(i, j+1))
                    value += 4;
                
                // Left
                if(IsWall(i-1, j))
                    value += 8;
                
                m_grid[i][j].type = static_cast<TILE>(value);
            }
        }
    }
}

// Sets the textures for the level based on tile types
void Level::SetTextures()
{
    for(int i=0; i<m_gridSize.x; i++)
    {
        for(int j=0; j<m_gridSize.y; j++)
        {
            m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(m_grid[i][j].type)]));
        }
    }
}

// Creates the entry and exit to the level
void Level::GenerateEntryExit()
{
    int startLocation = -1;
    int endLocation = -1;
    
    // Set the entry/exit to top/bottom or left/right depending on level dimentions
    if(m_gridSize.x > m_gridSize.y)
    {
        // Place entry/exit on left/right of level
        while(startLocation == -1)
        {
            int index = std::rand() % m_gridSize.x;
            if(m_grid[1][index].type == TILE::FLOOR)
            {
                startLocation = index;
            }
        }
        
        while(endLocation == -1)
        {
            int index = std::rand() % m_gridSize.x;
            if(m_grid[m_gridSize.x-2][index].type == TILE::FLOOR)
            {
                endLocation = index;
            }
        }
        
        // Set the tile textures for the entrance and exit tiles.
        SetTile(0, startLocation, TILE::WALL_ENTRANCE_LEFT);
        SetTile(m_gridSize.x-1, endLocation, TILE::WALL_DOOR_LOCKED_RIGHT);
        
        // Save spawn position coordinates
        m_spawnLocation = GetActualTileLocation(1, startLocation);
        // Save exit door location
        m_doorTileIndices = sf::Vector2i(m_gridSize.x-1, endLocation);
       
    }
    else
    {
        // Place entry/exit on top/bottom of level
        while(startLocation == -1)
        {
            int index = std::rand() % m_gridSize.x;
            if(m_grid[index][m_gridSize.y - 2].type == TILE::FLOOR)
            {
                startLocation = index;
            }
        }
        
        while(endLocation == -1)
        {
            int index = std::rand() % m_gridSize.x;
            if(m_grid[index][1].type == TILE::FLOOR)
            {
                endLocation = index;
            }
        }
        
        // Set the tile textures for the entrance and exit tiles.
        SetTile(startLocation, m_gridSize.y - 1, TILE::WALL_ENTRANCE);
        SetTile(endLocation, 0, TILE::WALL_DOOR_LOCKED);
        
        // Save spawn position coordinates
        m_spawnLocation = GetActualTileLocation(startLocation, m_gridSize.y-2);
        // Save exit door location
        m_doorTileIndices = sf::Vector2i(endLocation, 0);
    }
}

// Loads a level from a .txt file.
bool Level::LoadLevelFromFile(std::string fileName)
{
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

	return true;
}

// Checks if a given tile is a wall block.
bool Level::IsWall(int i, int j)
{
	if (TileIsValid(i, j))
		return m_grid[i][j].type <= TILE::WALL_INTERSECTION;
	else
		return false;
}

// Unlocks the door in the level.
void Level::UnlockDoor()
{
    TILE exitTile = GetTile(m_doorTileIndices.x, m_doorTileIndices.y)->type;
    
    if(exitTile == TILE::WALL_DOOR_LOCKED || exitTile == TILE::WALL_DOOR_LOCKED_RIGHT)
    {
        // The locked and unlocked doors are next to each other in the enum
        // So adding 1 to the current tile will get the unlocked door
        SetTile(m_doorTileIndices.x, m_doorTileIndices.y, static_cast<TILE>(static_cast<int>(exitTile)+1));
    }
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex)
{
	Tile* tile = &m_grid[columnIndex][rowIndex];

    // Spikey floor is not considered 'floor' so items don't spawn on it and it
    // doesn't get spatted by 'alt floor' tiles.
	return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile& tile)
{
	return ((tile.type == TILE::FLOOR) || (tile.type == TILE::FLOOR_ALT) || (tile.type == TILE::FLOOR_SPIKES));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const
{
	return TILE_SIZE;
}

void Level::ResetNodes()
{
    for (int i=0; i<m_gridSize.x; i++) {
        for(int j=0; j<m_gridSize.y; j++)
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
	for (int i = 0; i < m_gridSize.x; i++)
	{
		for (int j = 0; j < m_gridSize.y; j++)
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
