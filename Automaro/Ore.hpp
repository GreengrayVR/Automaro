#pragma once

class Ore : public IPlaceable
{
public:
	Ore(World* world, std::string name, int count);

	void Update(float deltaTime) override;
};
