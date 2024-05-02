#include "pch.hpp"
#include "Player.hpp"

Player::Player(World* world)
	: Object(world)
	, m_Inventory(this)
{
	SetPriority(0);

	AddComponent(std::make_unique<ViewASCII>('p', 1));

	InputManager& inputManager = GetWorld()->GetGame()->GetInputManager();
	inputManager.AddKeyboardHandler(Key::W, this);
	inputManager.AddKeyboardHandler(Key::A, this);
	inputManager.AddKeyboardHandler(Key::S, this);
	inputManager.AddKeyboardHandler(Key::D, this);
	inputManager.AddKeyboardHandler(Key::Q, this);
	inputManager.AddKeyboardHandler(Key::E, this);
	inputManager.AddKeyboardHandler(Key::F, this);
	inputManager.AddKeyboardHandler(Key::Alpha1, this);
	inputManager.AddKeyboardHandler(Key::Alpha2, this);
	inputManager.AddKeyboardHandler(Key::Alpha3, this);
	inputManager.AddKeyboardHandler(Key::Alpha4, this);
	inputManager.AddKeyboardHandler(Key::Alpha5, this);
	inputManager.AddKeyboardHandler(Key::Alpha6, this);
	inputManager.AddKeyboardHandler(Key::ArrowUp, this);
	inputManager.AddKeyboardHandler(Key::ArrowRight, this);
	inputManager.AddKeyboardHandler(Key::ArrowDown, this);
	inputManager.AddKeyboardHandler(Key::ArrowLeft, this);
}

Player::~Player()
{
	InputManager& inputManager = GetWorld()->GetGame()->GetInputManager();
	inputManager.RemoveKeyboardHandler(Key::W, this);
	inputManager.RemoveKeyboardHandler(Key::A, this);
	inputManager.RemoveKeyboardHandler(Key::S, this);
	inputManager.RemoveKeyboardHandler(Key::D, this);
	inputManager.RemoveKeyboardHandler(Key::Q, this);
	inputManager.RemoveKeyboardHandler(Key::E, this);
	inputManager.RemoveKeyboardHandler(Key::F, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha1, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha2, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha3, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha4, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha5, this);
	inputManager.RemoveKeyboardHandler(Key::Alpha6, this);
	inputManager.RemoveKeyboardHandler(Key::ArrowUp, this);
	inputManager.RemoveKeyboardHandler(Key::ArrowRight, this);
	inputManager.RemoveKeyboardHandler(Key::ArrowDown, this);
	inputManager.RemoveKeyboardHandler(Key::ArrowLeft, this);
}

void Player::Move(Key direction)
{
	Vector pos = GetTransform().GetPosition();
	if (direction == Key::W)
		pos += { 0, -1 };
	else if (direction == Key::S)
		pos += { 0, 1 };
	else if (direction == Key::A)
		pos += { -1, 0 };
	else if (direction == Key::D)
		pos += { 1, 0 };

	GetWorld()->GetMap().Move(this, pos);
}

void Player::OnKeyDown(Key key)
{
	if (key == Key::W ||
		key == Key::S ||
		key == Key::A ||
		key == Key::D)
	{
		Move(key);
	}
	else if (key == Key::Q)
	{
		GetInventory().PickUp();
	}
	else if (key == Key::E)
	{
		GetInventory().ToggleView();
	}
	else if (key == Key::F)
	{
		const Vector& pos = GetTransform().GetPosition();
		ObjectIterator<IMachine> it = GetWorld()->GetMap().GetObjectIteratorInCell<IMachine>(pos);
		if (!it.Next()) return;

		IMachine* machine = it.Get();
		machine->SetEnabled(!machine->GetEnabled());
		GetWorld()->GetGame()->GetPopupManager().ShowText(
			std::format(
				"Machine {} {}",
				machine->GetName(),
				machine->GetEnabled() ? "enabled" : "disabled"
			)
		);
	}
	else if (key == Key::Alpha1)
		GetInventory().GetHotbar().Select(0);
	else if (key == Key::Alpha2)
		GetInventory().GetHotbar().Select(1);
	else if (key == Key::Alpha3)
		GetInventory().GetHotbar().Select(2);
	else if (key == Key::Alpha4)
		GetInventory().GetHotbar().Select(3);
	else if (key == Key::Alpha5)
		GetInventory().GetHotbar().Select(4);
	else if (key == Key::Alpha6)
		GetInventory().GetHotbar().Select(5);
	else if (key == Key::ArrowUp)
		GetInventory().GetHotbar().Place();
	else if (key == Key::ArrowRight)
		GetInventory().GetHotbar().Place();
	else if (key == Key::ArrowDown)
		GetInventory().GetHotbar().Place();
	else if (key == Key::ArrowLeft)
		GetInventory().GetHotbar().Place();
}

Inventory& Player::GetInventory()
{
	return m_Inventory;
}
