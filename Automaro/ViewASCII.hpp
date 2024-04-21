#pragma once

class ViewASCII : public IView
{
public:
	ViewASCII(char representation = '0', int priority = 0);

	char GetRepresentation() const;
	void SetRepresentation(char value);

	int GetPriority() const;
	void SetPriority(int priority);

	std::unique_ptr<IComponent> Clone() const override;

private:
	char m_cRepresentation;
	int m_iPriority;
};
