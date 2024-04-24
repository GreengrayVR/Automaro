#include "pch.hpp"
#include "Miner.hpp"

Miner::Miner(World* world, float miningSpeed)
	: IMachine(world, "Miner", 1, miningSpeed)
{
	FindComponent<ViewASCII>()->SetRepresentation('M');
}

void Miner::EarlyUpdate()
{
	auto pos = GetTransform().GetPosition() + Vector::Down();
	IPlaceable* placeable = GetWorld()->GetMap().GetPlaceable(pos);
	m_MinedItem = dynamic_cast<Item*>(placeable);
	SetRunning(m_MinedItem != nullptr);
}

void Miner::OnComplete()
{
	if (m_ItemOutput)
	{
		if (!m_ItemOutput->Transfer(m_MinedItem, 1)) // TODO: reverse transfer
		{
			(void)GetWorld()->GetMap().Release(m_MinedItem->GetTransform().GetPosition(), 0);
		}
	}
	else
	{
		m_ItemOutput = std::unique_ptr<Item>(new Item(*m_MinedItem));
		m_ItemOutput->SetCount(0);
		if (!m_ItemOutput->Transfer(m_MinedItem, 1))
		{
			(void)GetWorld()->GetMap().Release(m_MinedItem->GetTransform().GetPosition(), 0);
		}
	}

	TransferOutput(1);
}

void Miner::LateUpdate()
{
}

void Miner::OnPlace()
{
	Reset();
}

void Miner::OnPickup()
{
	GetWorld()->GetMap().ScheduleRemovePlaceable(this);
}
