#include "pch.hpp"
#include "Inventory.hpp"

Inventory::Inventory(Player* player)
	: m_pPlayer(player)
	, m_Hotbar(this)
{
	SetPriority(1);

	InputManager& inputManager = m_pPlayer->GetWorld()->GetGame()->GetInputManager();
	inputManager.AddKeyboardHandler(Key::W, this);
	inputManager.AddKeyboardHandler(Key::S, this);
	inputManager.AddKeyboardHandler(Key::C, this);
	inputManager.AddKeyboardHandler(Key::D, this);
	inputManager.AddKeyboardHandler(Key::A, this);
	inputManager.AddKeyboardHandler(Key::Alpha1, this);
	inputManager.AddKeyboardHandler(Key::Alpha2, this);
	inputManager.AddKeyboardHandler(Key::Alpha3, this);
	inputManager.AddKeyboardHandler(Key::Alpha4, this);
	inputManager.AddKeyboardHandler(Key::Alpha5, this);
	inputManager.AddKeyboardHandler(Key::Alpha6, this);
}

Inventory::~Inventory()
{
	InputManager& inputManager = m_pPlayer->GetWorld()->GetGame()->GetInputManager();
	inputManager.RemoveKeyboardHandler(Key::W, this);
	inputManager.RemoveKeyboardHandler(Key::S, this);
	inputManager.RemoveKeyboardHandler(Key::C, this);
	inputManager.RemoveKeyboardHandler(Key::D, this);
	inputManager.RemoveKeyboardHandler(Key::A, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha1, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha2, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha3, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha4, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha5, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha6, this);
}

void Inventory::Add(std::unique_ptr<Item> item)
{
	int slot = FindItem(item.get());

	if (slot == -1)
		m_vItems.push_back(std::move(item));
	else
		GetItem(slot)->SetCount(GetItem(slot)->GetCount() + item->GetCount());
}

bool Inventory::Drop(int slot)
{
	if (GetItems().size() == 0) return false;

	// move selection if dropping last item
	if (slot == GetItems().size() - 1)
		Select(slot - 1);

	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	std::unique_ptr<Item> item = Release(slot);
	m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText(std::format("Item [{}] ({}) dropped", item.get()->GetName(), item.get()->GetCount()));
	m_pPlayer->GetWorld()->GetMap().AddObject(std::move(item), pos);
	return true;
}

PlaceOperation Inventory::Place(int slot)
{
	if (GetItems().size() == 0) return PlaceOperation::Error;
	
	if (!GetItem(slot)->IsPlaceable())
	{
		m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText("Can't place this");
		return PlaceOperation::Error;
	}

	std::unique_ptr<Item>& item = GetItem(slot);

	// move selection if placing last item
	if (item->GetCount() - 1 <= 0 && slot == GetItems().size() - 1)
		Select(slot - 1);

	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	std::unique_ptr<IPlaceable> placeable;
	item->SetCount(item->GetCount() - 1);

	m_pPlayer->GetWorld()->GetGame()->GetPopupManager().ShowText(std::format("Machine [{}] placed", item->GetName()));

	if (item->GetCount() < 1)
	{
		placeable = std::unique_ptr<IPlaceable>(static_cast<IPlaceable*>(Release(slot).release()));
		placeable->SetCount(1);
		m_pPlayer->GetWorld()->GetMap().AddPlaceable(std::move(placeable), pos);
		return PlaceOperation::PlacedAndEmpty;
	}
	else
	{
		placeable = item->CloneT<IPlaceable>();
		placeable->SetCount(1);
		m_pPlayer->GetWorld()->GetMap().AddPlaceable(std::move(placeable), pos);
		return PlaceOperation::Placed;
	}
}

bool Inventory::PickUp()
{
	Map& map = m_pPlayer->GetWorld()->GetMap();
	PopupManager& popup = m_pPlayer->GetWorld()->GetGame()->GetPopupManager();
	const auto& pos = m_pPlayer->GetTransform().GetPosition();
	ObjectIterator<Item> it = map.GetObjectIteratorInCell<Item>(pos);

	if (it.Next())
	{
		if (!it.Get()->IsPickupable())
		{
			popup.ShowText("Item can't be picked up!");
			return false;
		}

		if (IPlaceable* placeable = dynamic_cast<IPlaceable*>(it.Get()))
			placeable->OnPickup();

		Add(it.Release());
		popup.ShowText("Item picked up!");
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

Hotbar& Inventory::GetHotbar()
{
	return m_Hotbar;
}

std::vector<std::unique_ptr<Item>>& Inventory::GetItems()
{
	return m_vItems;
}

std::unique_ptr<Item>& Inventory::GetItem(int slot)
{
	return m_vItems[slot];
}

int Inventory::FindItem(Item* item)
{
	if (item == nullptr) return -1;

	for (int i = 0; i < m_vItems.size(); i++)
		if (item->IsSimilar(m_vItems[i].get()))
			return i;

	return -1;
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
	else if (key == Key::Alpha1)
		GetHotbar().SetItem(GetSelected().second, 0);
	else if (key == Key::Alpha2)
		GetHotbar().SetItem(GetSelected().second, 1);
	else if (key == Key::Alpha3)
		GetHotbar().SetItem(GetSelected().second, 2);
	else if (key == Key::Alpha4)
		GetHotbar().SetItem(GetSelected().second, 3);
	else if (key == Key::Alpha5)
		GetHotbar().SetItem(GetSelected().second, 4);
	else if (key == Key::Alpha6)
		GetHotbar().SetItem(GetSelected().second, 5);
}
