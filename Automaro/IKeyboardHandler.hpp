#pragma once


class IKeyboardHandler
{
public:
	virtual ~IKeyboardHandler();

	virtual void OnKeyDown(Key key) = 0;

	int GetPriority() const;
	void SetPriority(int priority);

private:
	int m_iPriority;
};
