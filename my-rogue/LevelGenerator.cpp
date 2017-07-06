//
//  LevelComponent.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 29/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "LevelGenerator.hpp"

void LevelGenerator::SmoothWalls(LevelGrid& grid)
{
    for(int i=0; i<grid.GetDimentions().x; i++)
    {
        for(int j=0; j<grid.GetDimentions().y; j++)
        {
            if(grid.IsWall(sf::Vector2u(i,j)))
            {
                // Calculate bit mask
                int value = 0;
                
                TILE type = grid[i][j].type;
                
                // Top
                if(grid.IsWall(sf::Vector2u(i,j-1)))
                    value += 1;
                
                // Right
                if(grid.IsWall(sf::Vector2u(i+1, j)))
                    value += 2;
                
                // Bottom
                if(grid.IsWall(sf::Vector2u(i, j+1)))
                    value += 4;
                
                // Left
                if(grid.IsWall(sf::Vector2u(i-1, j)))
                    value += 8;
                
                grid[i][j].type = static_cast<TILE>(value);
            }
        }
    }
}

void LevelGenerator::CreateEntryExit(LevelGrid& grid)
{
    int startLocation = -1;
    int endLocation = -1;
    sf::Vector2u dimentions = grid.GetDimentions();
    
    // Set the entry/exit to top/bottom or left/right depending on level dimentions
    if(dimentions.x > dimentions.y)
    {
        // Place entry/exit on left/right of level
        while(startLocation == -1)
        {
            int index = std::rand() % dimentions.y;
            if(grid[1][index].type == TILE::FLOOR)
            {
                startLocation = index;
            }
        }
        
        while(endLocation == -1)
        {
            int index = std::rand() % dimentions.y;
            if(grid[dimentions.x-2][index].type == TILE::FLOOR)
            {
                endLocation = index;
            }
        }
        
        // Set the tile textures for the entrance and exit tiles.
        grid[0][startLocation].type = TILE::WALL_ENTRANCE_LEFT;
        grid[dimentions.x-1][endLocation].type = TILE::WALL_DOOR_LOCKED_RIGHT;
        
        grid.SetEntryPosition(sf::Vector2u(0,startLocation));
        grid.SetExitPosition(sf::Vector2u(dimentions.x-1,endLocation));
        
        // Spawn position is the tile next to the entry tile
        grid.SetSpawnPosition(sf::Vector2u(1, startLocation));
        
    }
    else
    {
        // Place entry/exit on top/bottom of level
        while(startLocation == -1)
        {
            int index = std::rand() % dimentions.x;
            if(grid[index][dimentions.y - 2].type == TILE::FLOOR)
            {
                startLocation = index;
            }
        }
        
        while(endLocation == -1)
        {
            int index = std::rand() % dimentions.x;
            if(grid[index][1].type == TILE::FLOOR)
            {
                endLocation = index;
            }
        }
        
        // Set the tile textures for the entrance and exit tiles.
        grid[startLocation][dimentions.y - 1].type =  TILE::WALL_ENTRANCE;
        grid[endLocation][0].type = TILE::WALL_DOOR_LOCKED;
        
        grid.SetEntryPosition(sf::Vector2u(startLocation, dimentions.y - 1));
        grid.SetExitPosition(sf::Vector2u(endLocation, 0));
        
        // Spawn position is the tile next to the entry tile
        grid.SetSpawnPosition(sf::Vector2u(startLocation, dimentions.y-2));
    }
}
