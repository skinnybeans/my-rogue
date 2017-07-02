//
//  LevelComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 29/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "LevelGeneratorComponent.hpp"
#include <iostream>

LevelGeneratorComponent::LevelGeneratorComponent()
{}

void LevelGeneratorComponent::GenerateLevel(std::vector<std::vector<Tile>>* grid, sf::Vector2u size)
{
    m_grid = grid;
    m_gridSize = size;
    
    ResetGrid();
    
    // Generate the initial grid pattern
    for(int i=0; i<size.x; i++)
    {
        for(int j=0; j<size.y; j++)
        {
            // Remember arrays are 0 based so every second tile will have an odd index
            if((i%2 != 0) && (j%2 != 0))
            {
                // Odd tiles are empty.
                //grid[i][j].type = TILE::EMPTY;
                grid->at(i)[j].type = TILE::EMPTY;
            }
            else
            {
                // Even tiles become wall
                //grid[i][j].type = TILE::WALL_TOP;
                grid->at(i)[j].type = TILE::WALL_TOP;
            }
            //grid[i][j].sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);
            grid->at(i)[j].sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);
        }
    }
}

void LevelGeneratorComponent::ResetGrid()
{
    // Store the column and row information for each node.
    m_grid->clear();
    m_grid->resize(m_gridSize.x);
    for (int i = 0; i < m_gridSize.x; i++)
    {
        m_grid->at(i).clear();
        m_grid->at(i).resize(m_gridSize.y);
        for (int j = 0; j < m_gridSize.y; j++)
        {
            auto cell = &(m_grid->at(i)[j]);
            cell->columnIndex = i;
            cell->rowIndex = j;
        }
    }
}

// Generates random paths through the level
void LevelGeneratorComponent::CreatePath(sf::Vector2u start)
{
    // Store the current tile
    Tile* currentTile = &m_grid->at(start.x)[start.y];
    
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
        if(IsValidTile(sf::Vector2i(dx, dy)))
        {
            
            Tile* nextTile = &m_grid->at(dx)[dy];
            
            // Check if tile has been visited before
            if(nextTile->type == TILE::EMPTY)
            {
                // Set the tile to floor
                nextTile->type = TILE::FLOOR;
                
                // Smash wall between the two grid spaces
                int ddx = currentTile->columnIndex + (directions[i].x/2);
                int ddy = currentTile->rowIndex + (directions[i].y/2);
                
                Tile* wall = &m_grid->at(ddx)[ddy];
                
                wall->type = TILE::FLOOR;
                
                // Move to next tile
                CreatePath(sf::Vector2u(dx, dy));
            }
        }
    }
}

void LevelGeneratorComponent::CreateRooms(int roomCount)
{
    for(int i=0; i<roomCount; i++)
    {
        // Generate room size
        int height = std::rand() % 3 + 1;
        int width = std::rand() % 3 + 1;
        
        // Choose starting location
        int startX = std::rand() % (m_gridSize.x-2) + 2;
        int startY = std::rand() % (m_gridSize.y-2) + 2;
        
        // Punch out the room
        for(int j=0; j<width; j++)
        {
            for(int k=0; k<height; k++)
            {
                // Coords for the tile
                int currentX = startX + j;
                int currentY = startY + k;
                
                // Do we have a tile inside the bounds of the level
                if(IsValidTile(sf::Vector2i(currentX, currentY)))
                {
                    // Don't put holes in the edges of the level. Monsters will escape...
                    if(currentX != 0 && currentY != 0 && currentX != m_gridSize.x-1 && currentY != m_gridSize.y-1)
                    {
                        Tile* tile = &m_grid->at(currentX)[currentY];
                        tile->type = TILE::FLOOR;
                    }
                }
            }
        }
    }
}


bool LevelGeneratorComponent::IsValidTile(sf::Vector2i location)
{
    bool validColumn, validRow;
    
    validColumn = ((location.x >= 0) && (location.x < m_gridSize.x));
    validRow = ((location.y >= 0) && (location.y < m_gridSize.y));
    
    return (validColumn && validRow);
}
