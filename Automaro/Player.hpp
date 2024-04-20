#pragma once

class Player : public Object, public IKeyboardHandler
{
public:
	Player(World* world);
	~Player();
	
	void Move(Key direction);

	virtual void OnKeyDown(Key key) override;

	Inventory& GetInventory();

private:

	Inventory m_Inventory;
};
