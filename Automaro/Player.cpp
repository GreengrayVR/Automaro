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
}

Inventory& Player::GetInventory()
{
	return m_Inventory;
}
