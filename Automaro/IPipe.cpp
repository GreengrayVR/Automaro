#include "pch.hpp"
#include "IPipe.hpp"

IPipe::IPipe(World* world, const ItemPipePrefab* prefab, int count)
	: IPlaceable(world, prefab, count)
	, IWorkable(world, prefab->GetTransferSpeed())
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
			m_Output->SetOutput(this);

			m_View->SetRepresentation('|');
			return;
		}
	}
}

void IPipe::OnPickup()
{
	GetWorld()->GetMap().RemovePlaceable(this, false);

	if (!m_Output) return;
	m_Output->SetOutput(nullptr);
	m_Output = nullptr;
}

void IPipe::EarlyUpdate()
{
	m_View->SetBackgroundColor(m_ItemInput.get() != nullptr ? BGColor::Red : BGColor::Black);
	SetRunning(m_ItemInput.get() != nullptr);
}

void IPipe::OnComplete()
{
	GetWorld()->GetGame()->GetPopupManager().ShowText("pipe update", .3f);
}

void IPipe::LateUpdate()
{
}

void IPipe::SetRepresentation(char value)
{
	m_View->SetRepresentation(value);
}
