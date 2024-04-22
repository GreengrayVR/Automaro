#include "pch.hpp"
#include "Miner.hpp"

Miner::Miner(World* world, float miningSpeed)
	: IMachine(world, "Miner", 1, miningSpeed)
{
	FindComponent<ViewASCII>()->SetRepresentation('M');
}

void Miner::EarlyUpdate()
{
	auto pos = GetTransform().GetPosition() + Vector{ 0, 1 };
	IPlaceable* placeable = GetWorld()->GetMap().GetPlaceable(pos);
	m_OreInput = dynamic_cast<Ore*>(placeable);
	SetRunning(m_OreInput != nullptr);
}

void Miner::OnComplete()
{
	if (m_OreOutput)
	{
		if (!m_OreOutput->Transfer(m_OreInput, 1)) // TODO: reverse transfer
		{
			(void)GetWorld()->GetMap().Release(m_OreInput->GetTransform().GetPosition(), 0);
		}
	}
	else
	{
		m_OreOutput = std::unique_ptr<Ore>(new Ore(*static_cast<Ore*>(m_OreInput)));
		m_OreOutput->SetCount(0);
		if (!m_OreOutput->Transfer(m_OreInput, 1))
		{
			(void)GetWorld()->GetMap().Release(m_OreInput->GetTransform().GetPosition(), 0);
		}
	}
}

void Miner::LateUpdate()
{
}

Ore* Miner::GetOreOutput()
{
	return m_OreOutput.get();
}
