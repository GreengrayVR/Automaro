#include "pch.hpp"
#include "Ore.hpp"

Ore::Ore(World* world, std::string name, int count)
	: IPlaceable(world, name + " Ore", count, false)
{
}

void Ore::Update(float deltaTime)
{
}

void Ore::OnPlace()
{
}
