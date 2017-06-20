//-------------------------------------------------------------------------------------
// Enemy.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"
#include "Level.hpp"

class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

	/**
	 * Applies the given amount of damage to the enemy.
	 * @param damage The amount of damage to deal to the enemy.
	 */
	void Damage(int damage);

	/**
	 * Checks if the enemy has taken enough damage that they are now dead.
	 * @return True if the enemy is dead.
	 */
	bool IsDead();
    
    /**
     * Recalculates the target position of the enemy
     * @param level Reference to the level the enemy and target are in
     * @param playerPosition target location for the enemy
     */
    void UpdatePathfinding(Level & level, sf::Vector2f playerPosition);
    
    /**
     * Updates the enemy ai
     * @param timeDelta time since last update
     */
    void Update(float timeDela) override;

    
private:
    
    /**
     * Current enemy path
     */
    std::vector<sf::Vector2f> m_path;
    
    /**
     * Debug sprite for path
     */
    sf::Sprite m_pathSprite;
    
    /**
     * Debug font for path
     */
    sf::Font m_pathFont;
    
    /**
     * Debug text for path
     */
    sf::Text m_pathText;
    
    /**
     * How close the enemy must be to chase the player
     */
    float m_visionRadius;
    
};
#endif
