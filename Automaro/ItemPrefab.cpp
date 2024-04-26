#include "pch.hpp"

ItemPrefab::ItemPrefab(std::string name)
	: m_sName(name)
{
}

const std::string& ItemPrefab::GetName() const
{
	return m_sName;
}

MinerPrefab::MinerPrefab(std::string name)
	: ItemPrefab(name)
{
}

const float& MinerPrefab::GetMiningSpeed() const
{
	return m_fMiningSpeed;
}

ItemPipePrefab::ItemPipePrefab(std::string name)
	: ItemPrefab(name)
{
}

const float& ItemPipePrefab::GetTransferSpeed() const
{
	return m_fTransferSpeed;
}
