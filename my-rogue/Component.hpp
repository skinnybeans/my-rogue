//
//  component.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 8/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

class Component
{
public:
    /**
     * Default constructor
     */
    Component();
    
    /**
     * Virtual destructor to ensure correct deletion through base class pointers
     */
    virtual ~Component(){};
    
    /**
     * Update the component based on how much time has elapsed
     * @param timeDelta time step in seconds
     */
    virtual void Update(float timeDelta){};
};

#endif /* component_hpp */
