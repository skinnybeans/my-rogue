//
//  LevelGrid.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 30/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef LevelGrid_hpp
#define LevelGrid_hpp

#include "PCH.hpp"

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

using TileGrid = std::vector<std::vector<Tile>>;
using TileRow = std::vector<Tile>;

class LevelGrid {
public:
    /**
     * Default constructor
     */
    LevelGrid();
    
    /**
     * Clears the grid and resets it to the given dimentions
     * @param size size in tiles
     */
    void ResetGrid(sf::Vector2u dimentions);
    
    /**
     * Returns the underlying tile grid
     * @return reference to the tile grid
     */
    TileGrid& GetTileGrid();
    
    /**
     * Sets the position of the level entry
     */
    void SetEntryPosition(sf::Vector2u tileIndex);
    
    /**
     * Gets the position of the level entry
     */
    sf::Vector2u GetEntryPosition() const;
    
    /**
     * Sets the position of the level exit
     */
    void SetExitPosition(sf::Vector2u tileIndex);
    
    /**
     * Gets the position of the level exit
     */
    sf::Vector2u GetExitPosition() const;
    
    /**
     * Sets the player spawn position inside the level.
     * This should be the space next to the entry
     */
    void SetSpawnPosition(sf::Vector2u tileIndex);
    
    /**
     * Gets the player spawn position
     */
    sf::Vector2u GetSpawnPosition() const;
    
    
    /**
     * Returns the dimentions of the level grid
     */
    sf::Vector2u GetDimentions() const;
    
    /**
     * Checks if a given index is a valid tile
     * @param tileIndex x and y index of the tile to check
     * @return true if a tile exists at the given index
     */
    bool IsValidTile(sf::Vector2u tileIndex);
    
    /**
     * Checks if a given index is a wall tile
     * @param tileIndex x and y index of the tile to check
     * @return true if a tile exists at the given index
     */
    bool IsWall(sf::Vector2u tileIndex);
    
    
private:
    
    /**
     * The actual tile objects
     */
    TileGrid m_grid;
    
    /**
     * Dimentions of the level grid
     */
    sf::Vector2u m_dimentions;
    
    /**
    * location of the entry door
    */
    sf::Vector2u m_entryPosition;
    
    /**
     * location of the exit door
     */
    sf::Vector2u m_exitPosition;
    
    /**
     * where the player will spawn
     */
    sf::Vector2u m_spawnPosition;
    
public:
    /**
     * Overload operator [] to return a tile row.
     * Allows the use of array notation to access all elements
     */
    TileRow& operator[] (std::size_t idx)
    {
        return m_grid[idx];
    }
    
    const TileRow& operator[] (std::size_t idx) const
    {
        return m_grid[idx];
    }
};


#endif /* LevelGrid_hpp */
