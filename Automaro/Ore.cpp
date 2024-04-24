#include "pch.hpp"
#include "Ore.hpp"

Ore::Ore(World* world, std::string name, int count)
	: IPlaceable(world, name + " Ore", count, false)
{
}

void Ore::OnPlace()
{
}

void Ore::OnPickup()
{
	GetWorld()->GetMap().ScheduleRemovePlaceable(this);
}
