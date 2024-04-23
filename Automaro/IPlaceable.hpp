#pragma once

class IPlaceable : public Item
{
public:
	IPlaceable(World* world, std::string name, int count, bool pickupable = true);
	virtual ~IPlaceable();

	virtual void Update(float deltaTime) = 0;
	virtual void OnPlace() = 0;
};