//
//  BacktrackerLevelGenerator.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 4/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef BacktrackerLevelGenerator_hpp
#define BacktrackerLevelGenerator_hpp

#include "LevelGenerator.hpp"
#include "PCH.hpp"
#include "Tile.hpp"
#include "LevelConfig.hpp"

class BacktrackerLevelGenerator : public LevelGenerator
{
public:
    BacktrackerLevelGenerator();
    void GenerateLevel(std::vector<std::vector<Tile>>* grid, LevelConfig& config) override;
private:
    void CreatePath(std::vector<std::vector<Tile>>* grid, LevelConfig& config, sf::Vector2u start);
    void CreateRooms(std::vector<std::vector<Tile>>* grid, LevelConfig& config);
    void ResetGrid(std::vector<std::vector<Tile>>* grid, LevelConfig& config);
    bool IsValidTile(sf::Vector2i location, sf::Vector2u dimentions);
};


// Uses the recursive backtracker algorithm for generating the maze

#endif /* BacktrackerLevelGenerator_hpp */
