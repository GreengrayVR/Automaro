#pragma once
#include "IWorkable.hpp"

class Miner : public IMachine
{
public:
	Miner(World* world, int count);
	
	virtual void OnPlace() override;
	virtual void OnPickup() override;
	virtual void EarlyUpdate() override;
	virtual void OnComplete() override;
	virtual void LateUpdate() override;

	std::unique_ptr<Item> Clone() const;

private:
	Item* m_MinedItem;
};
