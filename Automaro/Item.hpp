#pragma once

class Item : public Object
{
public:
	virtual ~Item();

	Item(World* world, std::string name, int count, bool solid = false, bool placeable = false);

	int GetCount() const;
	std::string GetName() const;
	bool IsPlaceable() const;

private:
	int m_iCount;
	std::string m_sName;
	bool m_bPlaceable;
};
