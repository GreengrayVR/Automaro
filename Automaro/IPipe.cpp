#include "pch.hpp"
#include "IPipe.hpp"

IPipe::IPipe(World* world, float transferSpeed)
	: IPlaceable(world, "Item Pipe")
	, IWorkable(world, transferSpeed)
{
	m_View = FindComponent<ViewASCII>();
}

IPipe::~IPipe()
{
}

void IPipe::OnPlace()
{
	Vector pos = GetTransform().GetPosition();
	Map& map = GetWorld()->GetMap();

	// find machine and connect to it
	for (const auto& dir : m_Directions)
	{
		auto placeable = map.GetPlaceable(pos + dir.second);
		if (m_Output = dynamic_cast<IWorkable*>(placeable))
		{
			GetWorld()->GetGame()->GetPopupManager().ShowText(std::format("x{} y{}", dir.second.x, dir.second.y));
			m_Output->SetOutput(this);
			return;
		}
	}
}

void IPipe::OnPickup()
{
	GetWorld()->GetMap().ScheduleRemovePlaceable(this);
	m_Output->SetOutput(nullptr);
	m_Output = nullptr;
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
