#pragma once

class Ore : public IPlaceable
{
public:
	Ore(World* world, const ItemPrefab* prefab, int count);

	virtual void OnPlace() override;
	virtual void OnPickup() override;
};
