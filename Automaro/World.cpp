#include "pch.hpp"
#include "World.hpp"

World::World(Game* game, size_t width, size_t height)
	: m_Map(width, height)
	, m_pGame(game)
{
	Populate();
}

void World::Populate()
{
	m_pPlayer = static_cast<Player*>(GetMap().AddObject(std::move(std::make_unique<Player>(this)), { 5, 5 }));
	m_pPlayer->GetInventory().Add(std::make_unique<Item>(this, &ItemPrefab_IronIngot, 1));
	m_pPlayer->GetInventory().Add(std::make_unique<ItemPipe>(this, 10));
	m_pPlayer->GetInventory().Add(std::make_unique<Miner>(this, 1));

	GetMap().AddPlaceable(std::make_unique<Ore>(this, &ItemPrefab_IronOre, 5), { 3 , 9 });
}

void World::Update(float deltaTime)
{
	GetMap().Update(deltaTime);
}

Game* World::GetGame() const
{
	return m_pGame;
}

Map& World::GetMap()
{
	return m_Map;
}

Player* World::GetPlayer() const
{
	return m_pPlayer;
}
