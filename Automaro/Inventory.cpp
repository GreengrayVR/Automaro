#include "pch.hpp"
#include "Inventory.hpp"

Inventory::Inventory(Player* player)
	: m_pPlayer(player)
{
	SetPriority(1);

	InputManager& inputManager = m_pPlayer->GetWorld()->GetGame()->GetInputManager();
	inputManager.AddKeyboardHandler(Key::W, this);
	inputManager.AddKeyboardHandler(Key::S, this);
	inputManager.AddKeyboardHandler(Key::C, this);
	inputManager.AddKeyboardHandler(Key::D, this);
	inputManager.AddKeyboardHandler(Key::A, this);
}

Inventory::~Inventory()
{
	InputManager& inputManager = m_pPlayer->GetWorld()->GetGame()->GetInputManager();
	inputManager.RemoveKeyboardHandler(Key::W, this);
	inputManager.RemoveKeyboardHandler(Key::S, this);
	inputManager.RemoveKeyboardHandler(Key::C, this);
	inputManager.RemoveKeyboardHandler(Key::D, this);
	inputManager.RemoveKeyboardHandler(Key::A, this);
}

void Inventory::Add(std::unique_ptr<Item> item)
{
	m_vItems.push_back(std::move(item));
}

bool Inventory::Drop(int slot)
{
	if (GetItems().size() == 0) return false;

	// move selection if dropping last item
	if (slot == GetItems().size() - 1)
		Select(slot - 1);

	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	std::unique_ptr<Item> item = Release(slot);
	m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText(MakeString("Item [", item.get()->GetName(), "] (", item.get()->GetCount(), ") dropped"));
	m_pPlayer->GetWorld()->GetMap().AddObject(std::move(item), pos);
	return true;
}

bool Inventory::Place(int slot)
{
	if (GetItems().size() == 0) return false;
	
	if (!GetItem(slot).get()->IsPlaceable())
	{
		m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText("Can't place this");
		return false;
	}

	// move selection if placing last item
	if (slot == GetItems().size() - 1)
		Select(slot - 1);

	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	std::unique_ptr<Item> item = Release(slot);
	m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText(MakeString("Machine [", item.get()->GetName(), "] (", item.get()->GetCount(), ") placed"));
	
	std::unique_ptr<IPlaceable> placeable(static_cast<IPlaceable*>(item.release()));
	m_pPlayer->GetWorld()->GetMap().AddPlaceable(std::move(placeable), pos);

	return true;
}

bool Inventory::PickUp()
{
	Map& map = m_pPlayer->GetWorld()->GetMap();
	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	ObjectIterator<Item> it = map.GetObjectIteratorInCell<Item>(pos);

	if (it.Next())
	{
		if (!it.Get()->IsPickupable())
		{
			m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText("Item can't be picked up!");
			return false;
		}

		Add(it.Release());
		m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText("Item picked up!");
		return true;
	}

	return false;
}

bool Inventory::IsVisible()
{
	return m_bIsVisible;
}

void Inventory::ToggleView()
{
	m_bIsVisible = !m_bIsVisible;

	if (m_bIsVisible)
		m_pPlayer->GetWorld()->GetGame()->GetInputManager().SetPriority(GetPriority());
	else
		m_pPlayer->GetWorld()->GetGame()->GetInputManager().PopPriority();
}

std::vector<std::unique_ptr<Item>>& Inventory::GetItems()
{
	return m_vItems;
}

std::unique_ptr<Item>& Inventory::GetItem(int slot)
{
	return m_vItems[slot];
}

void Inventory::Remove(std::unique_ptr<Item> item)
{
	m_vItems.erase(std::ranges::find(m_vItems, item));
}

void Inventory::Remove(int slot)
{
	m_vItems.erase(m_vItems.begin() + slot);
}

std::unique_ptr<Item> Inventory::Release(int slot)
{
	auto item = std::move(GetItem(slot));
	Remove(slot);
	return item;
}

void Inventory::Select(int slot)
{
	if (m_vItems.empty() || slot < 0) return;
	m_iSelectedIndex = slot;
}

void Inventory::SelectNext()
{
	if (m_vItems.empty()) return;

	if (m_iSelectedIndex + 1 >= m_vItems.size())
	{
		Select(0);
		return;
	}

	Select(m_iSelectedIndex + 1);
}

void Inventory::SelectPrev()
{
	if (m_vItems.empty()) return;

	if (m_iSelectedIndex - 1 < 0)
	{
		Select((int)m_vItems.size() - 1);
		return;
	}

	Select(m_iSelectedIndex - 1);
}

std::pair<int, Item*> Inventory::GetSelected()
{
	if (m_vItems.empty()) return std::pair<int, Item*>();

	return std::make_pair(m_iSelectedIndex, m_vItems[m_iSelectedIndex].get());
}

void Inventory::OnKeyDown(Key key)
{
	if (key == Key::W)
		SelectPrev();
	else if (key == Key::S)
		SelectNext();
	else if (key == Key::C)
		ToggleView();
	else if (key == Key::D)
		Drop(GetSelected().first);
	else if (key == Key::A)
		Place(GetSelected().first);
}
