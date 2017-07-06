//
//  LevelGrid.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 30/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "LevelGrid.hpp"

// Default constructor
LevelGrid::LevelGrid()
{}

// Return the underlying grid.
// Ideally this shouldn't be needed
TileGrid& LevelGrid::GetTileGrid()
{
    return m_grid;
}

// Clear the grid and set to specified dimentions
void LevelGrid::ResetGrid(sf::Vector2u dimentions)
{
    m_dimentions = dimentions;
    
    // Store the column and row information for each node.
    m_grid.clear();
    m_grid.resize(dimentions.x);
    for (int i = 0; i < dimentions.x; i++)
    {
        m_grid[i].clear();
        m_grid[i].resize(dimentions.y);
        for (int j = 0; j < dimentions.y; j++)
        {
            auto cell = &(m_grid[i][j]);
            cell->columnIndex = i;
            cell->rowIndex = j;
        }
    }
}

// Get the level grid dimentions
sf::Vector2u LevelGrid::GetDimentions() const
{
    return m_dimentions;
}

// Get the entry tile position
sf::Vector2u LevelGrid::GetEntryPosition() const
{
    return m_entryPosition;
}

// Set the entry tile position
void LevelGrid::SetEntryPosition(sf::Vector2u position)
{
    m_entryPosition = position;
}

// Get the exit tile position
sf::Vector2u LevelGrid::GetExitPosition() const
{
    return m_exitPosition;
}

// Set the exit tile position
void LevelGrid::SetExitPosition(sf::Vector2u position)
{
    m_exitPosition = position;
}

// Get the spawn position
sf::Vector2u LevelGrid::GetSpawnPosition() const
{
    return m_spawnPosition;
}

// Set the spawn position
void LevelGrid::SetSpawnPosition(sf::Vector2u position)
{
    m_spawnPosition = position;
}

// Does the given index fall within the level grid
bool LevelGrid::IsValidTile(sf::Vector2u tileIndex)
{
    bool valid = tileIndex.x < m_dimentions.x && tileIndex.y < m_dimentions.y;
    
    return (valid);
}

// Is the given index a wall tile
bool LevelGrid::IsWall(sf::Vector2u tileIndex)
{
    if (IsValidTile(tileIndex))
        return m_grid[tileIndex.x][tileIndex.y].type <= TILE::WALL_INTERSECTION;
    else
        return false;
}
