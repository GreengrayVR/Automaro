#pragma once
#include "MachineManager.hpp"

class IMachine : public IPlaceable
{
public:
	IMachine(World* world, std::string name, int count);
	virtual ~IMachine();
};
