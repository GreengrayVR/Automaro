#pragma once

class ViewASCII : public IView
{
public:
	ViewASCII(char representation = '0', int priority = 0);

	char GetRepresentation() const;
	void SetRepresentation(char value);

	FGColor GetForegroundColor();
	void SetForegroundColor(FGColor color);

	BGColor GetBackgroundColor();
	void SetBackgroundColor(BGColor color);

	int GetPriority() const;
	void SetPriority(int priority);

	virtual std::unique_ptr<IComponent> Clone() const override;

private:
	FGColor m_ForegroundColor;
	BGColor m_BackgroundColor;
	char m_cRepresentation;
	int m_iPriority;
};
