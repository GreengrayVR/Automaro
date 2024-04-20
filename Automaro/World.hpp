#pragma once

class Game;

class World
{
public:
	World(Game* game, size_t width, size_t height);

	void Populate();

	void Update(float deltaTime);

	Game* GetGame() const;

	Map& GetMap();

	Player* GetPlayer() const;

private:
	Player* m_pPlayer;
	Map m_Map;
	Game* m_pGame;
};
