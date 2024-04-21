#pragma once

class Item : public Object
{
public:
	virtual ~Item();

	Item(World* world, std::string name, int count, bool solid = false, bool placeable = false, bool pickupable = true);

	int GetCount() const;
	void SetCount(int count);
	std::string GetName() const;
	bool IsPlaceable() const;
	bool IsPickupable() const;
	bool Transfer(Item* item, int count);

private:
	int m_iCount;
	std::string m_sName;
	bool m_bPlaceable;
	bool m_bPickupable;
};
