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
	m_pPlayer->GetInventory().Add(std::make_unique<Item>(this, "Iron Ingot", 3));
	m_pPlayer->GetInventory().Add(std::make_unique<Item>(this, "Iron Ore", 256));
	m_pPlayer->GetInventory().Add(std::make_unique<Item>(this, "Copper Ingot", 1));
	m_pPlayer->GetInventory().Add(std::make_unique<Item>(this, "Gold Ingot", 1));
	m_pPlayer->GetInventory().Add(std::make_unique<Miner>(this, 30.f));
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
