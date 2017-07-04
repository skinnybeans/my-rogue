//
//  BacktrackerLevelGenerator.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 4/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "BacktrackerLevelGenerator.hpp"

BacktrackerLevelGenerator::BacktrackerLevelGenerator()
{}

void BacktrackerLevelGenerator::GenerateLevel(std::vector<std::vector<Tile>>* grid, LevelConfig& config)
{
    ResetGrid(grid, config);
    
    // Generate the initial grid pattern
    for(int i=0; i<config.dimentions.x; i++)
    {
        for(int j=0; j<config.dimentions.y; j++)
        {
            // Remember arrays are 0 based so every second tile will have an odd index
            if((i%2 != 0) && (j%2 != 0))
            {
                // Odd tiles are empty.
                grid->at(i)[j].type = TILE::EMPTY;
            }
            else
            {
                // Even tiles become wall
                grid->at(i)[j].type = TILE::WALL_TOP;
            }
            grid->at(i)[j].sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);
        }
    }
    
    CreatePath(grid, config, sf::Vector2u(1,1));
    CreateRooms(grid, config);
}

void BacktrackerLevelGenerator::ResetGrid(std::vector<std::vector<Tile>>* grid, LevelConfig& config)
{
    // Store the column and row information for each node.
    grid->clear();
    grid->resize(config.dimentions.x);
    for (int i = 0; i < config.dimentions.x; i++)
    {
        grid->at(i).clear();
        grid->at(i).resize(config.dimentions.y);
        for (int j = 0; j < config.dimentions.y; j++)
        {
            auto cell = &(grid->at(i)[j]);
            cell->columnIndex = i;
            cell->rowIndex = j;
        }
    }
}

// Generates random paths through the level
void BacktrackerLevelGenerator::CreatePath(std::vector<std::vector<Tile>>* grid, LevelConfig& config, sf::Vector2u start)
{
    // Store the current tile
    Tile* currentTile = &grid->at(start.x)[start.y];
    
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
        if(IsValidTile(sf::Vector2i(dx, dy), config.dimentions))
        {
            
            Tile* nextTile = &grid->at(dx)[dy];
            
            // Check if tile has been visited before
            if(nextTile->type == TILE::EMPTY)
            {
                // Set the tile to floor
                nextTile->type = TILE::FLOOR;
                
                // Smash wall between the two grid spaces
                int ddx = currentTile->columnIndex + (directions[i].x/2);
                int ddy = currentTile->rowIndex + (directions[i].y/2);
                
                Tile* wall = &grid->at(ddx)[ddy];
                
                wall->type = TILE::FLOOR;
                
                // Move to next tile
                CreatePath(grid, config, sf::Vector2u(dx, dy));
            }
        }
    }
}

void BacktrackerLevelGenerator::CreateRooms(std::vector<std::vector<Tile>>* grid, LevelConfig& config)
{
    for(int i=0; i<config.roomCount; i++)
    {
        // Generate room size
        int height = std::rand() % 3 + 1;
        int width = std::rand() % 3 + 1;
        
        // Choose starting location
        int startX = std::rand() % (config.dimentions.x-2) + 2;
        int startY = std::rand() % (config.dimentions.y-2) + 2;
        
        // Punch out the room
        for(int j=0; j<width; j++)
        {
            for(int k=0; k<height; k++)
            {
                // Coords for the tile
                int currentX = startX + j;
                int currentY = startY + k;
                
                // Do we have a tile inside the bounds of the level
                if(IsValidTile(sf::Vector2i(currentX, currentY), config.dimentions))
                {
                    // Don't put holes in the edges of the level. Monsters will escape...
                    if(currentX != 0 && currentY != 0 && currentX != config.dimentions.x-1 && currentY != config.dimentions.y-1)
                    {
                        Tile* tile = &grid->at(currentX)[currentY];
                        tile->type = TILE::FLOOR;
                    }
                }
            }
        }
    }
}


bool BacktrackerLevelGenerator::IsValidTile(sf::Vector2i location, sf::Vector2u dimentions)
{
    bool validColumn, validRow;
    
    validColumn = ((location.x >= 0) && (location.x < dimentions.x));
    validRow = ((location.y >= 0) && (location.y < dimentions.y));
    
    return (validColumn && validRow);
}
