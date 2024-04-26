#include "pch.hpp"
#include "IPlaceable.hpp"

IPlaceable::~IPlaceable()
{
}

IPlaceable::IPlaceable(World* world, const ItemPrefab* prefab, int count, bool pickupable)
	: Item(world, prefab, count, true, true, pickupable)
{
}