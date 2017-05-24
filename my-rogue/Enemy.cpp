#include "PCH.hpp"
#include "Enemy.hpp"
#include "ResourcePath.hpp"

#include "spdlog/spdlog.h"

#include <iostream>
#include <cmath>
// Default constructor.
Enemy::Enemy()
{
	// Set stats.
	m_health = std::rand() % 41 + 80;
	m_attack = std::rand() % 5 + 6;
	m_defense = std::rand() % 5 + 6;
	m_strength = std::rand() % 5 + 6;
	m_dexterity = std::rand() % 5 + 6;
	m_stamina = std::rand() % 5 + 6;

	// Set speed.
	m_speed = rand() % 51 + 150;
    
    // Set default target
    m_path.clear();
    
    // Set the sprite
    int textureID = TextureManager::AddTexture(resourcePath() + "/resources/spr_path.png");
    m_pathSprite.setTexture(TextureManager::GetTexture(textureID));
    
    // Set the sprite origin
    sf::Vector2u spriteSize = m_pathSprite.getTexture()->getSize();
    m_pathSprite.setOrigin(sf::Vector2f(static_cast<float>(spriteSize.x / 2), static_cast<float>(spriteSize.y / 2)));
    
    // Set the font.
    m_pathFont.loadFromFile(resourcePath() + "/resources/fonts/04B_03__.TTF");
    
    // Set the text.
    m_pathText.setFont(m_pathFont);
    m_pathText.setCharacterSize(12);
}

// Override the default draw function.
void Enemy::Draw(sf::RenderWindow& window, float timeDelta)
{
    // Call base class draw first
    Object::Draw(window, timeDelta);
    
    // DEBUG Draw the current path
    for (int i = 0; i < m_path.size(); i++)
    {
        // draw the path sprite
        m_pathSprite.setPosition(m_path[i]);
        window.draw(m_pathSprite);
        // set the path index
        std::ostringstream ss;
        ss << i;
        std::string str(ss.str());
        m_pathText.setString(str);
        m_pathText.setPosition(m_path[i]);
        window.draw(m_pathText);
    }
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
	m_health -= damage;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (m_health <= 0);
}

// Updates the enemy
void Enemy::Update(float timeDelta)
{
    // Check that enemy has somewhere to move to
    if(!m_path.empty())
    {
        sf::Vector2f targetLocation = m_path.front();
        
        // Check how far away the enemy is from the target location
        m_velocity = sf::Vector2f(targetLocation.x - m_position.x, targetLocation.y - m_position.y);
        
        // Enemy is less than 10 units from x and y target locations
        if(std::abs(m_velocity.x) < 10.f && std::abs(m_velocity.y) < 10.f)
        {
            // Enemy considered to have reached the location
            m_path.erase(m_path.begin());
        }
        else // We have moving to do
        {
            // First normalise the movement vector
            float length = std::pow(m_velocity.x, 2) + std::pow(m_velocity.y, 2);
            m_velocity.x = m_velocity.x / length;
            m_velocity.y = m_velocity.y / length;
            
            // Now use the normalised vector, enemy speed and time step to move
            m_position.x = m_velocity.x * (m_speed * timeDelta);
            m_position.y = m_velocity.y * (m_speed * timeDelta);
            
            m_sprite.setPosition(m_position);
        }
    }
    
    // Call base class update
    Entity::Update(timeDelta);
}

// Updates the target position of the enemy
void Enemy::UpdatePathfinding(Level & level, sf::Vector2f playerPosition)
{
    std::vector<Tile*> openList;        // Nodes that need checking
    std::vector<Tile*> closedList;      // Nodes that have been checked
    std::vector<Tile*> pathList;        // Nodes on final path
    std::vector<Tile*>::iterator position;  // Position in the list
    Tile* currentNode;      // Current working node
    
    level.ResetNodes();
    
    Tile* startNode = level.GetTile(m_position);
    Tile* goalNode = level.GetTile(playerPosition);
    
    // create a logger for debug pathing output
    //auto pathLogger = spdlog::stdout_logger_mt("enemy_path");
    
    std::cout << "-----Starting path calc-----" << std::endl;
    std::cout << "Goal x: " << goalNode->columnIndex << " y: " << goalNode->rowIndex << std::endl;
    std::cout << "Start x: " << startNode->columnIndex << " y: " << startNode->rowIndex << std::endl << std::endl;
    
    
    // Is enemy at same tile as player
    if(startNode == goalNode)
    {
        m_path.clear();
        return;
    }
    
    // Calculate H cost for each tile
    // H = estimated cost to location
    // Uses Manhatten distance for cost
    for (int i=0; i<level.GetSize().x; i++)
    {
        for(int j=0; j<level.GetSize().y; j++)
        {
            int rowOffset;
            int columnOffet;
            Tile* node = level.GetTile(i,j);
            
            rowOffset = abs(node->rowIndex - goalNode->rowIndex);
            columnOffet = abs(node->columnIndex - goalNode->columnIndex);
            
            node->H = rowOffset + columnOffet;
        }
    }
    
    // Add the starting node to the open list
    openList.push_back(startNode);
    
    // Main loop for the pathfinding
    while(!openList.empty())
    {
        // Find the node with the lowest F value
        // Then make it the current node
        int lowestF = INT_MAX;
        
        std::cout << "*choosing next node*" << std::endl;
        for(Tile* tile : openList)
        {
            std::cout << "checking F: " << tile->F << std::endl;
            if(tile->F < lowestF)
            {
                lowestF = tile->F;
                currentNode = tile;
            }
        }
        std::cout << "selected F: " << currentNode->F << std::endl;
        std::cout << "selected location x: " << currentNode->columnIndex << " y: " << currentNode->rowIndex << std::endl << std::endl;
        
        // Remove lowest cost node from the open list
        // Add it to close list
        position = std::find(openList.begin(), openList.end(), currentNode);
        
        // Not sure why this check is here... should never be at .end()
        if(position != openList.end())
        {
            openList.erase(position);
        }
        
        // if we are at .end() then there wont be a current node...
        closedList.push_back(currentNode);
        
        // Find all adjacent and valid nodes
        std::vector<Tile*> adjacentNodes;
        
        // Check if adjacent nodes are valid or not
        Tile* potentialNode = nullptr;
        
        // Check top. Row -1
        potentialNode = level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1);
        if((potentialNode != nullptr) && (level.IsFloor(*potentialNode)))
        {
            adjacentNodes.push_back(potentialNode);
        }
        
        // Check bottom. Row +1
        potentialNode = level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1);
        if((potentialNode != nullptr) && (level.IsFloor(*potentialNode)))
        {
            adjacentNodes.push_back(potentialNode);
        }
        
        // Check left. Col -1
        potentialNode = level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex);
        if((potentialNode != nullptr) && (level.IsFloor(*potentialNode)))
        {
            adjacentNodes.push_back(potentialNode);
        }
        
        // Check right. Col +1
        potentialNode = level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex);
        if((potentialNode != nullptr) && (level.IsFloor(*potentialNode)))
        {
            adjacentNodes.push_back(potentialNode);
        }
        
        // Now process the adjacent valid nodes
        std::cout << "*processing adjacent nodes*" << std::endl;
        for(Tile* nextNode: adjacentNodes)
        {
            std::cout << std::endl << "checking node x: " << nextNode->columnIndex << " y: " << nextNode->rowIndex << std::endl;
            // Found the goal
            if(nextNode == goalNode)
            {
                std::cout << "found goal x: " << nextNode->columnIndex << " y: " << nextNode->rowIndex << std::endl;
                // Now construct the path to the goal
                nextNode->parentNode = currentNode;
                
                while(nextNode->parentNode != nullptr)
                {
                    pathList.push_back(nextNode);
                    nextNode = nextNode->parentNode;
                }
                
                // Break out of the for loop
                openList.clear();
                
                break;
            }
            else // didn't find goal node
            {
                std::cout << "didn't find goal..." << std::endl;
                // If the node is not in the closed list
                position = std::find(closedList.begin(), closedList.end(), nextNode);
                if(position == closedList.end())
                {
                    std::cout << "Have not processed this node before" << std::endl;
                    
                    // If the node is not in the open list
                    position = std::find(openList.begin(), openList.end(), nextNode);
                    if(position == openList.end())
                    {
                        std::cout << "Have not touched this node before" << std::endl;
                        // Add the node to the open list
                        openList.push_back(nextNode);
                        
                        // Set the parent of the node to the current node
                        nextNode->parentNode = currentNode;
                        
                        // Calculate total cost of path to current node
                        // Each node costs 10 to navigate
                        nextNode->G = currentNode->G + 10;
                        
                        // Calculate F cost
                        // total movement cost + heuristic cost
                        nextNode->F = nextNode->G + nextNode->H;
                    }
                    else // Node exists in the open list
                    {
                        // Check if this path is quicker than the other
                        int tempG = currentNode->G + 10;
                        
                        if(tempG < nextNode->G)
                        {
                            std::cout << "Node gives shorter path" << std::endl;
                            nextNode->parentNode = currentNode;
                        }
                    }
                }
                // else node was in closed list and ignore it
            }
        }
        
    } // End path loop
    
    // Clear target movement positions
    m_path.clear();
    
    // Add the positions of the tiles on the path to the empty path
    std::cout << std::endl << "*final path*" << std::endl;
    for(Tile* tile : pathList)
    {
        m_path.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
        std::cout << "x: " << tile->columnIndex << " y: " << tile->rowIndex << std::endl;
    }
    
    // Path is ordered from goal -> enemy tso need to reverse it so it's enemy -> goal
    std::reverse(m_path.begin(),m_path.end());

    
    std::cout << "-----Finished path calc-----" << std::endl << std::endl << std::endl;
    
}
