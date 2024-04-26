#pragma once

class IPlaceable : public Item
{
public:
	IPlaceable(World* world, const ItemPrefab* prefab, int count = 1, bool pickupable = true);
	virtual ~IPlaceable();

	virtual void OnPlace() = 0;
	virtual void OnPickup() = 0;
};