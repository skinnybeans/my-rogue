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
    OpenRoomLevelGenerator();
    
    void GenerateLevel(LevelGrid& grid, LevelConfig& config) override;
    
private:
    
};

#endif /* OpenRoomLevelGenerator_hpp */
