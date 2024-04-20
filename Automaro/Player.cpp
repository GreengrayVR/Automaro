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
}

Inventory& Player::GetInventory()
{
	return m_Inventory;
}
