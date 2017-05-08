//
//  PoisonHeart.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 8/5/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef PoisonHeart_hpp
#define PoisonHeart_hpp

#include "Item.hpp"

#include <stdio.h>

class PoisonHeart : public Item
{
public:
    
    /**
     * Default constructor.
     */
    PoisonHeart();
    
    /**
     * Returns the amount of health that the heart gives.
     * @return The amount of health the heart gives.
     */
    int GetHealth() const;
    
private:
    
    /**
     * The amount of health the heart gives.
     */
    int m_health;
};

#endif /* PoisonHeart_hpp */
