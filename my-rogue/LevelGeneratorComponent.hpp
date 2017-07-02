//
//  LevelComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 29/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef LevelGeneratorComponent_hpp
#define LevelGeneratorComponent_hpp

#include "PCH.hpp"
#include "Tile.hpp"
#include "Level.hpp"

class LevelGeneratorComponent
{
public:
    LevelGeneratorComponent();
    
    void GenerateLevel(std::vector<std::vector<Tile>>* grid, sf::Vector2u size);
    void CreatePath(sf::Vector2u start);
    void CreateRooms(int roomCount);
private:
    void ResetGrid();
    bool IsValidTile(sf::Vector2i location);
    
    std::vector<std::vector<Tile>>* m_grid;
    
    sf::Vector2u m_gridSize;
    
};

#endif /* LevelGeneratorComponent_hpp */
