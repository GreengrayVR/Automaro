#include "pch.hpp"
#include "Game.hpp"

Game::Game(size_t map_width, size_t map_height)
	: m_World(this, map_width, map_height)
{

}

bool Game::Update(float deltaTime)
{
	m_InputManager.Update(deltaTime);
	m_World.Update(deltaTime);
	m_PopupManager.Update(deltaTime);
	m_Renderer.Draw(m_World, deltaTime);

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return true;
}

void Game::Run()
{
	auto startTime = std::chrono::steady_clock::now();

	while (IsRunning())
	{
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> deltaTime = currentTime - startTime;
		startTime = currentTime;

		Update(deltaTime.count());
	}
}

bool Game::IsRunning()
{
	return m_bIsRunning;
}

InputManager& Game::GetInputManager()
{
	return m_InputManager;
}

PopupManager& Game::GetPopupManager()
{
	return m_PopupManager;
}
