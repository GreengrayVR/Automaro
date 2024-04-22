#pragma once

class Miner : public IMachine
{
public:
	Miner(World* world, float miningSpeed);


	void EarlyUpdate() override;
	void OnComplete() override;
	void LateUpdate() override;

	Ore* GetOreOutput();

private:
	std::unique_ptr<Ore> m_OreOutput;
	Ore* m_OreInput;
};