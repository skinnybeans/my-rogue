#include "PCH.hpp"
#include "Item.hpp"

// Default constructor.
Item::Item()
{}

// Gets the item type.
ITEM Item::GetType() const
{
	return m_type;
}
