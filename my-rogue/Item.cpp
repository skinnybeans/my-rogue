#include "PCH.hpp"
#include "Item.hpp"
#include "ResourcePath.hpp"
#include "TransformComponent.hpp"

// Default constructor.
Item::Item() :
	m_name(""),
	m_textOffset({0.f, 0.f})
{
	// Load font.
	m_font.loadFromFile(resourcePath() + "/resources/fonts/ADDSBP__.TTF");
	m_text.setFont(m_font);

	// Setup the text.
	m_text.setCharacterSize(12);
}

// Gets the name of the item.
std::string Item::GetItemName() const
{
	return m_name;
}

// Sets the item name.
void Item::SetItemName(std::string name)
{
	// Store new name.
	m_name = name;

	// Set the item name.
	std::ostringstream ss;
	ss << m_name;
	std::string str(ss.str());
	m_text.setString(str);

	// Store the text offset needed when drawing.
	m_textOffset = sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

// Gets the item type.
ITEM Item::GetType() const
{
	return m_type;
}

// Draws the item and its name if it has one.
/*
void Item::Draw(sf::RenderWindow& window, float timeDelta)
{
    
    // Get the items position out for setting text and sprite location
    sf::Vector2f itemPosition = GetComponent<TransformComponent>()->GetPosition();
    
	// Draw the object.
	Object::Draw(window, timeDelta);

	// Draw the item name.
	m_text.setPosition(itemPosition.x - m_textOffset.x, (itemPosition.y - 30.f) - m_textOffset.y);
	window.draw(m_text);
}
*/
