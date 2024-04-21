#include "pch.hpp"
#include "IPlaceable.hpp"

IPlaceable::~IPlaceable()
{
}

IPlaceable::IPlaceable(World* world, std::string name, int count, bool pickupable)
	: Item(world, name, count, true, true, pickupable)
{
}