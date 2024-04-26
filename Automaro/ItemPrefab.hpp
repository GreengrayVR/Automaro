#pragma once

struct ItemPrefab
{
	ItemPrefab(std::string name);
	const std::string& GetName() const;
	std::string m_sName;
};

struct MinerPrefab : ItemPrefab
{
	MinerPrefab(std::string name);
	const float& GetMiningSpeed() const;
	float m_fMiningSpeed = 5.f;
};

struct ItemPipePrefab : ItemPrefab
{
	ItemPipePrefab(std::string name);
	const float& GetTransferSpeed() const;
	float m_fTransferSpeed = 1.f;
};




const inline ItemPrefab ItemPrefab_IronIngot("Iron Ingot");
const inline ItemPrefab ItemPrefab_IronOre("Iron Ore");
const inline MinerPrefab MinerPrefab_Miner("Miner");
const inline ItemPipePrefab ItemPipePrefab_ItemPipe("Item Pipe");
