#include "pch.hpp"
#include "Miner.hpp"

Miner::Miner(World* world, float miningSpeed)
	: IMachine(world, "Miner", 1)
	, m_fMiningSpeed(miningSpeed)
	, m_fTime(miningSpeed)
{
	FindComponent<ViewASCII>()->SetRepresentation('M');
}

float Miner::GetTime() const
{
	return m_fTime;
}

void Miner::Update(float deltaTime)
{
	auto pos = GetTransform().GetPosition() + Vector{ 0, 1 };
	IPlaceable* placeable = GetWorld()->GetMap().GetPlaceable(pos); // TODO: replace with proper function

	if (!placeable) return;


	m_fTime -= deltaTime;

	if (m_fTime < 0)
	{

		if (m_ItemOutput)
		{
			if (!m_ItemOutput->Transfer(placeable, 1)) // TODO: reverse transfer
			{
				(void)GetWorld()->GetMap().Release(placeable->GetTransform().GetPosition(), 0);
			}
		}
		else
		{
			m_ItemOutput = std::unique_ptr<Ore>(new Ore(*static_cast<Ore*>(placeable)));
			m_ItemOutput->SetCount(0);
			if (!m_ItemOutput->Transfer(placeable, 1))
			{
				(void)GetWorld()->GetMap().Release(placeable->GetTransform().GetPosition(), 0);
			}
		}

		m_fTime = m_fMiningSpeed;
	}
}
