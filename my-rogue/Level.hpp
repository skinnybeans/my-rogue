//-------------------------------------------------------------------------------------
// Level.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef LEVEL_H
#define LEVEL_H

#include "Torch.hpp"

// The width and height of each tile in pixels.
static int const TILE_SIZE = 50;

// The level tile type.
struct Tile {
	TILE type;							// The type of tile this is.
	int columnIndex;					// The column index of the tile.
	int rowIndex;						// The row index of the tile.
	sf::Sprite sprite;					// The tile sprite.
	int H;								// Heuristic / movement cost to goal.
	int G;								// Movement cost. (Total of entire path)
	int F;								// Estimated cost for full path. (G + H)
	Tile* parentNode;					// Node to reach this node.
};

class Level
{
public:
	/**
	 * Default constructor.
	 */
	Level();

	/** 
	 * Constructor.
	 * A renderWindow is needed in order for the level to calculate its position.
	 * @param window The game window.
	 */
	Level(sf::RenderWindow& window);

    /**
     * Sets the overlay color of the level tiles.
     * @param tileColor The new tile overlay color
     */
    void SetColor(sf::Color tileColor);
    
	/**
	 * Returns true if the given tile index is solid.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @return True if the given tile is solid.
	 */
	bool IsSolid(int columnIndex, int rowIndex);

	/**
	 * Sets the index of a given tile in the 2D game grid.
	 * This also changes the tile sprite, and is how tiles should be changed and set manually.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @param index The new index of the tile.
	 */
	void SetTile(int columnIndex, int rowIndex, TILE tileType);
    
    /**
     * Gets the world coordinates of a tile.
     * @param columnIndex The tile's column index
     * @param rowIndex The tile's row index
     * @return The coordinates of the tile
     */
    sf::Vector2f GetActualTileLocation(int columnIndex, int rowIndex);
    
    
    /**
     * Gets a valid tile to spawn an item/enemy
     * @return The coorindates to spawn the item
     */
    sf::Vector2f GetRandomSpawnLocation();

	/**
	 * Draws the level grid to the provided render window.
	 * @param window The render window to draw the level to.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	void Draw(sf::RenderWindow &window, float timeDelta);

	/**
	 * Gets the index of the given tile.
	 * @param columnIndex The column index of the tile to check.
	 * @param rowIndex The row index of the tile to check.
	 * @return The index of the given tile.
	 */
	TILE GetTileType(int columnIndex, int rowIndex) const;

	/**
	 * Loads a level from a text file.
	 * @param fileName The path to the level file to load.
	 * @return true if the level loaded succesfully.
	 */
	bool LoadLevelFromFile(std::string fileName);
    
    /**
     * Generates a random level
     * @return true if the level generated successfully.
     */
    bool GenerateLevel();

	/**
	 * Gets the tile at the given position.
	 * @param position The coordinates of the position to check.
	 * @return A pointer to the tile at the given location.
	 */
	Tile* GetTile(sf::Vector2f position);

	/**
	* Gets the tile at the given position in the level array.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The row that the tile is in.
	* @return A pointer to the tile if valid.
	*/
	Tile* GetTile(int columnIndex, int rowIndex);

	/**
	 * Gets the position of the level grid relative to the window.
	 * @return The position of the top-left of the level grid.
	 */
	sf::Vector2f GetPosition() const;
    
    /**
     * Get the coordinates of the spawn location
     * @return A vector containing cooreinates to the player spawn location
     *
     */
    sf::Vector2f GetSpawnLocation();

	/**
	 * Gets a vector of all torches in the level.
	 * @return A vector of shared_ptrs containing all torches in the level.
	 */
	std::vector<std::shared_ptr<Torch>>* GetTorches();

	/**
	 * Checks if a given tile is valid.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the tile is valid.
	 */
	bool TileIsValid(int columnIndex, int rowIndex);

	/**
	 * Gets the current floor number.
	 * @return The current floor.
	 */
	int GetFloorNumber() const;

	/**
	 * Gets the current room number.
	 * @return The current room.
	 */
	int GetLevelNumber() const;

	/**
	 * Gets the size of the level in terms of tiles.
	 * @return The size of the level grid.
	 */
	sf::Vector2i GetSize() const;

	/**
	 * Spawns a given number of torches in the level.
	 * @param torchCount The number of torches to create.
	 */
	void SpawnTorches(int torchCount);

	/**
	 * Unlocks the door in the level.
	 */
	void UnlockDoor();

	/**
	 * Return true if the given tile is a floor tile.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a floor tile.
	 */
	bool IsFloor(int columnIndex, int rowIndex);

	/**
	* Return true if the given tile is a floor tile.
	* @param tile The tile to check
	* @return True if the given tile is a floor tile.
	*/
	bool IsFloor(const Tile& tile);

	/**
	 * Returns the size of the tiles in the level.
	 * @return The size of the tiles in the level.
	 */
	int GetTileSize() const;

	/**
	* Adds a tile to the level.
	* These tiles are essentially sprites with a unique index. Once added, they can be loaded via the LoadLevelFromFile() function by including its index in the level data.
	* @param fileName The path to the sprite resource, relative to the project directory.
	* @param tileType The type of tile that is being added.
	* @return The index of the tile. This is used when building levels.
	*/
	int AddTile(std::string fileName, TILE tileType);
    
    /**
     * Resets the A* data of all level tiles.
     */
    void ResetNodes();

private:

	/**
	 * Checks if a given tile is a wall block.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a wall tile.
	 */
	bool IsWall(int columnIndex, int rowIndex);
    
    /**
     * Creates a path between two nodes in the recursive backtracker algorithm.
     */
    void CreatePath(int columnIndex, int rowIndex);
    
    /**
     * Creates a set number of rooms in the level.
     */
    void CreateRooms(int roomCount);
    
    
    /**
     * Create torches to place around the level.
     */
    void CreateTorches(int torchCount);
    
    /**
     * Calculates the correct textures for each tile
     */
    void CalculateWalls();
    
    /**
     * Sets the textures for all the level tiles based on tile type
     */
    void SetTextures();
    
    /**
     * Creates entry and exit points for the level
     */
    void GenerateEntryExit();
    
    /**
     * Clears and resets the level grid based on the currently set size
     */
    void ResetGrid();

private:
    
    // The size of the currently generated level grid
    sf::Vector2i m_gridSize;
    
	/**
	 * A 2D array that describes the level data.
	 * The type is Tile, which holds a sprite and an index.
	 */
    std::vector<std::vector<Tile>> m_grid;

	/**
	 * A vector off all the sprites in the level.
	 */
	std::vector<sf::Sprite> m_tileSprites;

	/**
	 * The position of the level relative to the window.
	 * This is to the top-left of the level grid.
	 */
	sf::Vector2i m_origin;

	/**
	* The floor number that the player is currently on.
    * Each floor consists of several levels
	*/
	int m_floorNumber;

	/**
	* The level number that the player is currently in.
	*/
	int m_levelNumber;

	/**
	* A 2D array that contains the room layout for the current floor.
	*/
	int m_roomLayout[3][10];

	/**
	 * An array containing all texture IDs of the level tiles.
	 */
	int m_textureIDs[static_cast<int>(TILE::COUNT)];

	/**
	 * The indices of the tile containing the levels door.
	 */
	sf::Vector2i m_doorTileIndices;

	/**
	 * A vector of all tiles in the level.
	 */
	std::vector<std::shared_ptr<Torch>> m_torches;
    
    /**
     * Return the coordinates of the spawn location
     */
    sf::Vector2f m_spawnLocation;
};
#endif
