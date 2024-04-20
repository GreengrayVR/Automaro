#include "pch.hpp"
#include "InputManager.hpp"

InputManager::InputManager()
{
	m_PriorityStack.push(0);
}

void InputManager::Update(float deltaTime)
{
	for (const auto& keyboardHandlers : m_KeyboardHandlers)
	{
		if (GetAsyncKeyState((char)keyboardHandlers.first) & 1)
		{
			for (const auto& keyHandler : keyboardHandlers.second)
			{
				auto keyhandlerpriority = keyHandler->GetPriority();
				auto currentpriority = GetCurrentPriority();
				if (keyhandlerpriority == currentpriority)
					keyHandler->OnKeyDown(keyboardHandlers.first);
			}
		}
	}
}

void InputManager::AddKeyboardHandler(Key key, IKeyboardHandler* keyboardHandler)
{
	m_KeyboardHandlers[key].push_back(keyboardHandler);
}

void InputManager::RemoveKeyboardHandler(Key key, IKeyboardHandler* keyboardHandler)
{
	auto& keyboardHandlers = m_KeyboardHandlers[key];
	keyboardHandlers.erase(std::ranges::find(keyboardHandlers, keyboardHandler));
}

void InputManager::SetPriority(int priority)
{
	m_PriorityStack.emplace(priority);
}

int InputManager::PopPriority()
{
	m_PriorityStack.pop();
	return m_PriorityStack.top();
}

int InputManager::GetCurrentPriority() const
{
	return m_PriorityStack.top();
}
