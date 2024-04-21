#pragma once

class IPlaceable : public Item
{
public:
	~IPlaceable();
	IPlaceable(World* world, std::string name, int count, bool pickupable = true);

	virtual void Update(float deltaTime) = 0;
};