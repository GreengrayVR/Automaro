#include "pch.hpp"
#include "IMachine.hpp"

IMachine::IMachine(World* world, const ItemPrefab* prefab, int count, float completeTime)
	: IPlaceable(world, prefab, count)
	, IWorkable(world, completeTime)
{
}

IMachine::~IMachine()
{
}
