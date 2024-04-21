#include "pch.hpp"
#include "Miner.hpp"

Miner::Miner(World* world, float miningSpeed)
	: IMachine(world, "Miner", 1)
	, m_fMiningSpeed(miningSpeed)
	, m_fTime(miningSpeed)
{
	FindComponent<ViewASCII>()->SetRepresentation('M');
}

void Miner::Update(float deltaTime)
{
	// check 1 direction if contains ore
	// then pick it up
}
