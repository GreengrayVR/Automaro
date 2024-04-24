#pragma once
#include "IWorkable.hpp"

class Miner : public IMachine
{
public:
	Miner(World* world, float miningSpeed);
	
	void OnPlace() override;
	void OnPickup() override;
	void EarlyUpdate() override;
	void OnComplete() override;
	void LateUpdate() override;

private:
	Item* m_MinedItem;
};
