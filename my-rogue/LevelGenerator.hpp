//
//  LevelGenerator.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 29/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef LevelGenerator_hpp
#define LevelGenerator_hpp

#include "PCH.hpp"
#include "LevelGrid.hpp"
#include "Level.hpp"
#include "LevelConfig.hpp"

class LevelGenerator
{
public:
    virtual void GenerateLevel(LevelGrid& grid, LevelConfig& config) = 0;
};

#endif /* LevelGeneratorComponent_hpp */
