#pragma once

class IMachine;

class MachineManager
{
public:
	void Update(float deltaTime);

private:

	std::vector<std::unique_ptr<IMachine>> m_vMachines;
};