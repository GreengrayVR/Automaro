#include "pch.hpp"
#include "Item.hpp"

Item::~Item()
{
}

Item::Item(World* world, std::string name, int count, bool solid, bool placeable)
	: Object(world, solid)
	, m_iCount(count)
	, m_sName(name)
	, m_bPlaceable(placeable)
{
	AddComponent(std::make_unique<ViewASCII>('.'));
}

int Item::GetCount() const
{
	return m_iCount;
}

std::string Item::GetName() const
{
	return m_sName;
}

bool Item::IsPlaceable() const
{
	return m_bPlaceable;
}
