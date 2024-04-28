#include "pch.hpp"
#include "IPipe.hpp"

IPipe::IPipe(World* world, const ItemPipePrefab* prefab, int count)
	: IPlaceable(world, prefab, count)
	, IWorkable(world, prefab->GetTransferSpeed())
	, m_View(nullptr)
{
}

IPipe::~IPipe()
{
}

void IPipe::OnPlace()
{
	m_View = FindComponent<ViewASCII>();
	Vector pos = GetTransform().GetPosition();
	Map& map = GetWorld()->GetMap();

	// find machine and connect to it
	for (const auto& dir : m_Directions)
	{
		auto placeable = map.GetPlaceable(pos + dir.second);
		if (m_Input = dynamic_cast<IWorkable*>(placeable))
		{
			if (dynamic_cast<IPipe*>(placeable))
			{
				GetWorld()->GetGame()->GetPopupManager().ShowText("connected to pipe", 1.f);
			}

			m_Input->SetOutput(this);

			if (dir.first == Direction::UP || dir.first == Direction::DOWN)
				m_View->SetRepresentation('|');
			if (dir.first == Direction::LEFT || dir.first == Direction::RIGHT)
				m_View->SetRepresentation('-');

			return;
		}
	}
}

void IPipe::OnPickup()
{
	GetWorld()->GetMap().RemovePlaceable(this, false);

	SetRepresentation('.');

	if (m_Input)
	{
		m_Input->SetOutput(nullptr);
		m_Input = nullptr;
	}

	if (m_Output)
	{
		m_Output->SetOutput(nullptr);
		m_Output = nullptr;
	}

	m_ItemInput.reset();
	m_ItemOutput.reset();
}

void IPipe::EarlyUpdate()
{
	if (m_View)
		m_View->SetBackgroundColor(m_ItemInput.get() != nullptr ? BGColor::Red : BGColor::Black);
	SetRunning(m_ItemInput.get() != nullptr);
}

void IPipe::OnComplete()
{
	if (!m_Output) return;
	if (m_Output->GetItemInput() != nullptr) return;

	m_ItemOutput = std::move(m_ItemInput);

	TransferOutput(1);
}

void IPipe::LateUpdate()
{
}

void IPipe::SetRepresentation(char value)
{
	if (m_View)
		m_View->SetRepresentation(value);
}
