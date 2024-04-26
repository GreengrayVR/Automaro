#pragma once

class IMachine : public IPlaceable, public IWorkable
{
public:
	IMachine(World* world, const ItemPrefab* prefab, int count, float completeTime);
	virtual ~IMachine();

};
