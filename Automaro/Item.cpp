#include "pch.hpp"
#include "Item.hpp"

Item::~Item()
{
}

Item::Item(World* world, std::string name, int count, bool solid, bool placeable, bool pickupable)
	: Object(world, solid)
	, m_iCount(count)
	, m_sName(name)
	, m_bPlaceable(placeable)
	, m_bPickupable(pickupable)
{
	AddComponent(std::make_unique<ViewASCII>('.'));
}

int Item::GetCount() const
{
	return m_iCount;
}

void Item::SetCount(int count)
{
	m_iCount = count;
}

std::string Item::GetName() const
{
	return m_sName;
}

bool Item::IsPlaceable() const
{
	return m_bPlaceable;
}

bool Item::IsPickupable() const
{
	return m_bPickupable;
}

bool Item::Transfer(Item* item, int count)
{
	m_iCount += count;
	item->SetCount(item->GetCount() - count);
	return item->GetCount() <= 0;
}
