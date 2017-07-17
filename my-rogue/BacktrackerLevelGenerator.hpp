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
#include "LevelGrid.hpp"
#include "LevelConfig.hpp"

class BacktrackerLevelGenerator : public LevelGenerator
{
public:
    BacktrackerLevelGenerator();
    virtual ~BacktrackerLevelGenerator(){};
    void GenerateLevel(LevelGrid& grid, LevelConfig& config) override;
private:
    void CreatePath(LevelGrid& grid, LevelConfig& config, sf::Vector2u start);
    void CreateRooms(LevelGrid& grid, LevelConfig& config);
};

// Uses the recursive backtracker algorithm for generating the maze

#endif /* BacktrackerLevelGenerator_hpp */
