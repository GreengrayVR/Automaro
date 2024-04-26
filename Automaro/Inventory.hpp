#pragma once

class Player; // delete

class Inventory : public IKeyboardHandler
{
public:
	Inventory(Player* player);
	~Inventory();

	void Add(std::unique_ptr<Item> item);
	bool Drop(int slot);
	bool Place(int slot);
	bool PickUp();
	bool IsVisible();
	void ToggleView();

	std::vector<std::unique_ptr<Item>>& GetItems();
	std::unique_ptr<Item>& GetItem(int slot);
	int FindItem(Item* item);

	virtual void OnKeyDown(Key key) override;

	std::pair<int, Item*> GetSelected();

private:
	void Remove(std::unique_ptr<Item> item);
	void Remove(int slot);
	std::unique_ptr<Item> Release(int slot);

	void Select(int slot);
	void SelectNext();
	void SelectPrev();

	const Player* m_pPlayer;
	std::vector<std::unique_ptr<Item>> m_vItems;

	bool m_bIsVisible = false;
	int m_iSelectedIndex = 0;
};
