//-------------------------------------------------------------------------------------
// Torch.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef TORCH_H
#define TORCH_H

#include "Object.hpp"


class Torch : public Object
{
private:
    enum class TORCH_STATE{
        BRIGHT,
        DARK,
        COUNT
    };
    
public:

	/**
	 * Default Constructor.
	 */
	Torch();

	/**
	 * Updates the brightness of the torch.
	 * @param timeDelta The time that has passed since the last update.
	 */
	void Update(float timeDelta) override;

	/**
	 * Gets the brightness modifier of the torch. This is used to create flicker.
	 * @return The brightness of the torch.
	 */
	float GetBrightness();

private:

	/**
	 * The max brightness of the torch
	 */
	float m_intensityBright;
    
    /**
     * The min brightness of the torch
     */
    float m_intensityDark;
    
    /**
     * The current brightness of the torch
     */
    float m_intensityCurrent;
    
    /**
     * How quickly the torch transitions between light and dark intensity
     */
    float m_transitionSpeed;
    
    /**
     * Current state of the torch
     */
    TORCH_STATE m_state;
};
#endif
