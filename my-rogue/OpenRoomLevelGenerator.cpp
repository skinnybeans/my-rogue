//
//  OpenRoomLevelGenerator.cpp
//  my-rogue
//
//  Created by Henrik Axelsson on 6/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#include "OpenRoomLevelGenerator.hpp"

OpenRoomLevelGenerator::OpenRoomLevelGenerator()
{}

void OpenRoomLevelGenerator::GenerateLevel(LevelGrid& grid, LevelConfig& config)
{
    // put walls around the edges of the level
    grid.ResetGrid(config.dimentions);
    
    for(int i=0; i<config.dimentions.x; i++)
    {
        for(int j=0; j<config.dimentions.y; j++)
        {
            grid[i][j].type = TILE::FLOOR;
            
            grid[i][j].sprite.setPosition(TILE_SIZE * i, TILE_SIZE * j);
        }
    }
    
    // top
    for(int i=0; i<config.dimentions.x; i++)
    {
        grid[i][0].type = TILE::WALL_TOP;
    }
    
    // bottom
    int y = config.dimentions.y - 1;
    for(int i=0; i<config.dimentions.x; i++)
    {
        grid[i][y].type = TILE::WALL_TOP;
    }
    
    // left side
    for(int i=0; i<config.dimentions.y; i++)
    {
        grid[0][i].type = TILE::WALL_TOP;
    }
    
    // right side
    int x = config.dimentions.x - 1;
    for(int i=0; i<config.dimentions.y; i++)
    {
        grid[x][i].type = TILE::WALL_TOP;
    }
    
    SmoothWalls(grid);
    CreateEntryExit(grid);
}
