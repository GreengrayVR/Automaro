#pragma once

class Item : public Object
{
public:
	Item(World* world, const ItemPrefab* prefab, int count, bool solid = false, bool placeable = false, bool pickupable = true);
	virtual ~Item();

	virtual std::unique_ptr<Item> Clone() const;

	template <typename T>
	std::unique_ptr<T> CloneT() const
	{
		auto tmp = Clone();

		if (auto result = dynamic_cast<T*>(tmp.get()))
			return std::unique_ptr<T>(static_cast<T*>(tmp.release()));

		assert(false);
		return {};
	}

	int GetCount() const;
	void SetCount(int count);
	const std::string& GetName() const;
	bool IsPlaceable() const;
	bool IsPickupable() const;
	void SetPickupable(bool pickupable);
	bool Transfer(Item* item, int count);

	bool IsSimilar(const Item* other) const;

private:
	int m_iCount;
	bool m_bPlaceable;
	bool m_bPickupable;
	const ItemPrefab* m_Prefab;
};
