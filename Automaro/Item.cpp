#include "pch.hpp"
#include "Item.hpp"

Item::Item(World* world, const ItemPrefab* prefab, int count, bool solid, bool placeable, bool pickupable)
	: Object(world, solid)
	, m_Prefab(prefab)
	, m_iCount(count)
	, m_bPlaceable(placeable)
	, m_bPickupable(pickupable)
{
	AddComponent(std::make_unique<ViewASCII>('.'));
}

Item::~Item()
{
}

std::unique_ptr<Item> Item::Clone() const
{
	return std::make_unique<std::decay_t<decltype(*this)>>(*this);
}

int Item::GetCount() const
{
	return m_iCount;
}

void Item::SetCount(int count)
{
	m_iCount = count;
}

const std::string& Item::GetName() const
{
	return m_Prefab->GetName();
}

bool Item::IsPlaceable() const
{
	return m_bPlaceable;
}

bool Item::IsPickupable() const
{
	return m_bPickupable;
}

void Item::SetPickupable(bool pickupable)
{
	m_bPickupable = pickupable;
}

bool Item::Transfer(Item* item, int count)
{
	m_iCount += count;
	item->SetCount(item->GetCount() - count);
	return item->GetCount() > 0;
}

bool Item::IsSimilar(const Item* other) const
{
	return m_Prefab == other->m_Prefab;
}
