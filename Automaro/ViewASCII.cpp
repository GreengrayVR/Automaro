#include "pch.hpp"
#include "ViewASCII.hpp"

ViewASCII::ViewASCII(char representation, int priority)
	: m_cRepresentation(representation)
	, m_iPriority(priority)
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
