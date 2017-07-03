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
#include "LevelConfig.hpp"

class LevelGeneratorComponent
{
public:
    LevelGeneratorComponent();
    void GenerateLevel(std::vector<std::vector<Tile>>* grid, LevelConfig& config);
private:
    void CreatePath(std::vector<std::vector<Tile>>* grid, LevelConfig& config, sf::Vector2u start);
    void CreateRooms(std::vector<std::vector<Tile>>* grid, LevelConfig& config);
    void ResetGrid(std::vector<std::vector<Tile>>* grid, LevelConfig& config);
    bool IsValidTile(sf::Vector2i location, sf::Vector2u dimentions);
};

#endif /* LevelGeneratorComponent_hpp */
