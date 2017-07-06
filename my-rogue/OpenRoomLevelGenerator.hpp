//
//  OpenRoomLevelGenerator.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 6/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef OpenRoomLevelGenerator_hpp
#define OpenRoomLevelGenerator_hpp

#include "LevelGenerator.hpp"

class OpenRoomLevelGenerator : public LevelGenerator
{
public:
    /**
     * Default constructor
     */
    OpenRoomLevelGenerator();
    
    /**
     * Generate the level grid
     * @param grid reference to a LevelGrid
     * @param config only uses grid size for this level type
     */
    void GenerateLevel(LevelGrid& grid, LevelConfig& config) override;
    
private:
    
};

#endif /* OpenRoomLevelGenerator_hpp */
