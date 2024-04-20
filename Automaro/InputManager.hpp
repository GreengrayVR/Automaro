#pragma once

class InputManager
{
public:
	InputManager();

	void Update(float deltaTime);

	void AddKeyboardHandler(Key key, IKeyboardHandler* keyboardHandler);
	void RemoveKeyboardHandler(Key key, IKeyboardHandler* keyboardHandler);

	void SetPriority(int priority);
	int PopPriority();
	int GetCurrentPriority() const;

private:
	std::map<Key, std::vector<IKeyboardHandler*>> m_KeyboardHandlers;
	std::stack<int> m_PriorityStack;
};
