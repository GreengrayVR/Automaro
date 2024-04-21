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
	m_fTime -= deltaTime;

	if (m_fTime < 0)
	{
		auto pos = GetTransform().GetPosition() + Vector{ 0, 1 };
		auto& objects = GetWorld()->GetMap().GetPlaceables(); // TODO: replace with proper function

		for (IPlaceable* placeable : objects)
		{
			if (placeable->GetTransform().GetPosition() == pos)
			{
				if (m_ItemOutput)
				{
					m_ItemOutput->Transfer(placeable, 1);
				}
				else
				{
					m_ItemOutput = std::unique_ptr<Ore>(new Ore(*static_cast<Ore*>(placeable)));
					m_ItemOutput->SetCount(0);
					m_ItemOutput->Transfer(placeable, 1);
				}
			}
		}

		m_fTime = m_fMiningSpeed;
	}
}
