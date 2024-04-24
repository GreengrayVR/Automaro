#pragma once

class Ore : public IPlaceable
{
public:
	Ore(World* world, std::string name, int count);

	void OnPlace() override;
	void OnPickup() override;
};
