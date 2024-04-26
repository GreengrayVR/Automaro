#include "pch.hpp"
#include "Ore.hpp"

Ore::Ore(World* world, const ItemPrefab* prefab, int count)
	: IPlaceable(world, prefab, count, false)
{
}

void Ore::OnPlace()
{
}

void Ore::OnPickup()
{
	GetWorld()->GetMap().RemovePlaceable(this);
}
