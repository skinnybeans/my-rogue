//-------------------------------------------------------------------------------------
// Object.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef OBJECT_H
#define OBJECT_H

#include "Component.hpp"

class Object
{
public:
	/**
	 * Default constructor.
	 */
	Object();
    
    /**
     * Virtual destructor to ensure correct deletion through base class pointers
     */
    virtual ~Object(){};

	/**
	 * Updates the game object. Called once per tick.
	 * This is a pure virtual function, and must be implemented by extending classes.
	 * @param timeDelta The time elapsed since the last tick in MS.
	 */
	virtual void Update(float timeDelta) {};
    
    /**
     * Attach a component to the object
     */
    template<typename T>
    std::shared_ptr<T> AttachComponent()
    {
        // Create an instance of the new component
        std::shared_ptr<T> newComponent = std::make_shared<T>();
        
        // Check a component of this type doesn't already exist
        for(std::shared_ptr<Component>& existingComponent : m_components)
        {
            if(std::dynamic_pointer_cast<T>(existingComponent) != nullptr)
            {
                // If it exists replace it and return the new component
                existingComponent = newComponent;
                return newComponent;
            }
        }
        // Component doesn't exist yet, add it to the Object
        m_components.push_back(newComponent);
        
        return newComponent;
    };
    
    /**
     * Returns a component from the object
     */
    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        // Search for a component of the given type
        for(std::shared_ptr<Component>& existingComponent : m_components)
        {
            if(std::dynamic_pointer_cast<T>(existingComponent) != nullptr)
            {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }
        
        // Didn't find one
        return nullptr;
    };

private:
    /**
     * Collection of components attached to this Object
     */
    std::vector<std::shared_ptr<Component>> m_components;
};
#endif
