#include "pch.hpp"
#include "IPipe.hpp"

IPipe::IPipe(World* world, float transferSpeed)
	: IMachine(world, "Item Pipe", 1, transferSpeed)
{
	m_View = FindComponent<ViewASCII>();
}

IPipe::~IPipe()
{
}

void IPipe::OnPlace()
{
	for (const auto& dir : GetDirections())
	{
		//dir
	}
}

void IPipe::EarlyUpdate()
{
}

void IPipe::OnComplete()
{
}

void IPipe::LateUpdate()
{
}

void IPipe::SetRepresentation(char value)
{
	m_View->SetRepresentation(value);
}

const std::vector<PipeDirection> IPipe::GetDirections() const
{
	return m_vDirections;
}
