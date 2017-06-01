#include "PCH.hpp"
#include "Level.hpp"
#include "ResourcePath.hpp"

#include <iostream>

// Default constructor.
Level::Level()
{
}

// Constructor.
Level::Level(sf::RenderWindow& window) : 
m_origin({ 0, 0 }),
m_floorNumber(1),
m_roomNumber(0),
m_doorTileIndices({ 0, 0 })
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

	// Calculate the top left of the grid.
	m_origin.x = (window.getSize().x - (GRID_WIDTH * TILE_SIZE));
	m_origin.x /= 2;

	m_origin.y = (window.getSize().y - (GRID_HEIGHT * TILE_SIZE));
	m_origin.y /= 2;

	// Store the column and row information for each node.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			auto cell = &m_grid[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
		}
	}
}

// Sets overlay color of level tiles
void Level::SetColor(sf::Color tileColor)
{
    for(int i=0; i<GRID_WIDTH; i++)
    {
        for(int j=0; j<GRID_HEIGHT; j++)
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
		return (((tileIndex != static_cast<int>(TILE::FLOOR)) && (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)));
	}
	else
		return false;
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::GetPosition() const
{
	return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
TILE Level::GetTileType(int columnIndex, int rowIndex) const
{
	// Check that the parameters are valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
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
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
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
    
    location.x = m_origin.x + (columnIndex * TILE_SIZE) + (TILE_SIZE / 2);
    location.y = m_origin.y + (rowIndex * TILE_SIZE) + (TILE_SIZE / 2);
    
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
        columnIndex = rand() % GRID_WIDTH;
        rowIndex = rand() % GRID_HEIGHT;
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
int Level::GetRoomNumber() const
{
	return m_roomNumber;
}

// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row)
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::GetSize() const
{
	return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position)
{
	// Convert the position to relative to the level grid.
	position.x -= m_origin.x;
	position.y -= m_origin.y;

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

// Generate a random level
bool Level::GenerateLevel()
{
    // Generate the initial grid pattern
    for(int i=0; i<GRID_WIDTH; i++)
    {
        for(int j=0; j<GRID_HEIGHT; j++)
        {
            // Remember arrays are 0 based so every second tile will have an odd index
            if((i%2 != 0) && (j%2 != 0))
            {
                // Odd tiles are empty.
                m_grid[i][j].type = TILE::EMPTY;
            }
            else
            {
                // Even tiles become wall
                m_grid[i][j].type = TILE::WALL_TOP;
                m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::WALL_TOP)]));
            }
            m_grid[i][j].sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));
        }
    }
    
    CreatePath(1,1);
    
    CreateRooms(15);
    
    return true;
}

void Level::CreatePath(int columnIndex, int  rowIndex)
{
    // Store the current tile
    Tile* currentTile = &m_grid[columnIndex][rowIndex];
    
    // Create a list of possible directions
    sf::Vector2i directions[] = {{0,-2},{2,0},{0,2},{-2,0}};
    
    // Shuffle the directions so we pick a random one first
    std::random_shuffle(std::begin(directions), std::end(directions));
    
    // Check all the tiles
    for(int i=0; i<4; i++)
    {
        int dx = currentTile->columnIndex + directions[i].x;
        int dy = currentTile->rowIndex + directions[i].y;
        
        // Check the grid position is valid
        if(TileIsValid(dx, dy))
        {
            
            Tile* nextTile = &m_grid[dx][dy];
            
            // Check if tile has been visited before
            if(nextTile->type == TILE::EMPTY)
            {
                // Set the tile to floor
                nextTile->type = TILE::FLOOR;
                nextTile->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));
                
                // Smash wall between the two grid spaces
                int ddx = currentTile->columnIndex + (directions[i].x/2);
                int ddy = currentTile->rowIndex + (directions[i].y/2);
                
                Tile* wall = &m_grid[ddx][ddy];
                
                wall->type = TILE::FLOOR;
                wall->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));
                
                // Move to next tile
                CreatePath(dx, dy);
            }
        }
    }
}

// Add rooms to the level
void Level::CreateRooms(int roomCount)
{
    for(int i=0; i<roomCount; i++)
    {
        // Generate room size
        int height = std::rand() % 3 + 1;
        int width = std::rand() % 3 + 1;
        
        // Choose starting location
        int startX = std::rand() % (GRID_WIDTH-2) + 2;
        int startY = std::rand() % (GRID_HEIGHT-2) + 2;
        
        // Punch out the room
        for(int j=0; j<width; j++)
        {
            for(int k=0; k<height; k++)
            {
                // Coords for the tile
                int currentX = startX + j;
                int currentY = startY + k;
                
                // Do we have a tile inside the bounds of the level
                if(TileIsValid(currentX, currentY))
                {
                    // Don't put holes in the edges of the level. Monsters will escape...
                    if(currentX != 0 && currentY != 0 && currentX != GRID_WIDTH-1 && currentY != GRID_HEIGHT-1)
                    {
                        Tile* tile = &m_grid[currentX][currentY];
                        tile->type = TILE::FLOOR;
                        tile->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));
                    }
                }
            }
        }
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
		for (int j = 0; j < GRID_HEIGHT; ++j)
		{
			for (int i = 0; i < GRID_WIDTH; ++i)
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
				cell.sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));

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
            torch->SetPosition(sf::Vector2f(location.x, location.y));
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
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, TILE::WALL_DOOR_UNLOCKED);
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
    for (int i=0; i<GRID_WIDTH; i++) {
        for(int j=0; j<GRID_HEIGHT; j++)
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
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			window.draw(m_grid[i][j].sprite);
		}
	}

	// Draw all torches.
	for (auto& torch : m_torches)
	{
		torch->Draw(window, timeDelta);
	}
}
