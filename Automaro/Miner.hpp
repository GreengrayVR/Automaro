#pragma once

class Miner : public IMachine
{
public:
	Miner(World* world, float miningSpeed);

	void Update(float deltaTime) override;

private:

	float m_fMiningSpeed;
};