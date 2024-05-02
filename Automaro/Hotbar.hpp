#pragma once

class Inventory;

class Hotbar
{
public:
	Hotbar(Inventory* inventory);

	std::pair<int, Item*> GetSelectedItem() const;
	void Place();
	Item* Select(int slot);
	Item* GetItem(int slot);
	void SetItem(Item* item, int slot);
	int Size() const;

private:
	std::array<Item*, 6> m_vItems;
	int m_iSlotSelected;
	Inventory* m_Inventory;
};
