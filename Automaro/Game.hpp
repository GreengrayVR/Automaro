#pragma once
#include "MachineManager.hpp"

class Game
{
public:
	Game(size_t map_width, size_t map_height);

	bool Update(float deltaTime);
	void Run();
	bool IsRunning();

	InputManager& GetInputManager();
	PopupManager& GetPopupManager();
	MachineManager& GetMachineManager();

private:
	InputManager m_InputManager;
	World m_World;
	Renderer m_Renderer;
	PopupManager m_PopupManager;
	MachineManager m_MachineManager;
	bool m_bIsRunning = true;
};
