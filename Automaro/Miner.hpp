#pragma once

class Miner : public IMachine
{
public:
	Miner(World* world, float miningSpeed);

	float GetTime() const;

	void Update(float deltaTime) override;

private:
	std::unique_ptr<Ore> m_ItemOutput;

	float m_fMiningSpeed;
	float m_fTime;
};