#include "pch.hpp"
#include "ViewASCII.hpp"

ViewASCII::ViewASCII(char representation, int priority)
	: m_cRepresentation(representation)
	, m_iPriority(priority)
	, m_ForegroundColor(FGColor::White)
	, m_BackgroundColor(BGColor::Black)
{
}

char ViewASCII::GetRepresentation() const
{
	return m_cRepresentation;
}

void ViewASCII::SetRepresentation(char value)
{
	m_cRepresentation = value;
}

FGColor ViewASCII::GetForegroundColor()
{
	return m_ForegroundColor;
}

void ViewASCII::SetForegroundColor(FGColor color)
{
	m_ForegroundColor = color;
}

BGColor ViewASCII::GetBackgroundColor()
{
	return m_BackgroundColor;
}

void ViewASCII::SetBackgroundColor(BGColor color)
{
	m_BackgroundColor = color;
}

int ViewASCII::GetPriority() const
{
	return m_iPriority;
}

void ViewASCII::SetPriority(int priority)
{
	m_iPriority = priority;
}

std::unique_ptr<IComponent> ViewASCII::Clone() const
{
	return std::unique_ptr<IComponent>(new ViewASCII(*this));
}
