//
//  TextComponent.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 14/6/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef TextComponent_hpp
#define TextComponent_hpp

#include "Component.hpp"
#include "TransformComponent.hpp"
#include <string>

class TextComponent : public Component
{
public:
    /**
     * default constructor
     */
    TextComponent();
    
    /**
     * Virtual destructor to ensure correct deletion through base class pointers
     */
    virtual ~TextComponent(){};
    
    /**
     * Sets the transform component to use for positioning
     * @param component the transform component
     */
    void SetTransformComponent(std::shared_ptr<TransformComponent> component);
    
    /**
     * Set the text
     * @param text the text
     */
    void SetText(std::string text);
    
    /**
     * Get the text
     * @return the text
     */
    std::string GetText();
    
    /**
     * Draw the text
     */
    void Draw(sf::RenderWindow &window, float timeDelta);

private:
    
    /**
     * A font object storing the name of the item.
     */
    sf::Font m_font;
    
    /**
     * A text object storing the name of the item.
     */
    sf::Text m_text;
    
    sf::Vector2f m_textOffset;
    
    std::shared_ptr<TransformComponent> m_transformComponent;
};

#endif /* TextComponent_hpp */
