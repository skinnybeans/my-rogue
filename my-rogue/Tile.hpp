//
//  Tile.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 30/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "PCH.hpp"

// The level tile type.
struct Tile {
    TILE type;							// The type of tile this is.
    int columnIndex;					// The column index of the tile.
    int rowIndex;						// The row index of the tile.
    sf::Sprite sprite;					// The tile sprite.
    int H;								// Heuristic / movement cost to goal.
    int G;								// Movement cost. (Total of entire path)
    int F;								// Estimated cost for full path. (G + H)
    Tile* parentNode;					// Node to reach this node.
};

#endif /* Tile_hpp */
