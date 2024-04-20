#pragma once

class IPlaceable : public Item
{
public:
	~IPlaceable();
	IPlaceable(World* world, std::string name, int count);

	virtual void Update(float deltaTime) = 0;
};