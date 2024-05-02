#include "pch.hpp"
#include "Hotbar.hpp"

Hotbar::Hotbar(Inventory* inventory)
	: m_Inventory(inventory)
	, m_iSlotSelected(0)
	, m_vItems()
{
}

void Hotbar::Place()
{
	int slot = m_Inventory->FindItem(GetSelectedItem().second);
	if (slot == -1) return;

	if (m_Inventory->Place(slot) == PlaceOperation::PlacedAndEmpty)
	{
		SetItem(nullptr, GetSelectedItem().first);
	}
}

std::pair<int, Item*>  Hotbar::GetSelectedItem() const
{ 
	return std::make_pair(m_iSlotSelected, m_vItems[m_iSlotSelected]);
}

Item* Hotbar::Select(int slot)
{
	if (slot > m_vItems.size() - 1 || slot < 0) return nullptr;
	m_iSlotSelected = slot;
	return GetItem(m_iSlotSelected);
}

Item* Hotbar::GetItem(int slot)
{
	return m_vItems[slot];
}

void Hotbar::SetItem(Item* item, int slot)
{
	if (slot > m_vItems.size() - 1 || slot < 0) return;

	for (int i = 0; i < Size(); i++)
		if (m_vItems[i] == item)
			m_vItems[i] = nullptr;

	m_vItems[slot] = item;
}

int Hotbar::Size() const
{
	return m_vItems.size();
}
