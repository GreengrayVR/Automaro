#include "pch.hpp"
#include "IPlaceable.hpp"

IPlaceable::~IPlaceable()
{
}

IPlaceable::IPlaceable(World* world, std::string name, int count)
	: Item(world, name, count, true, true)
{
}