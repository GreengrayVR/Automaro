#include "pch.hpp"
#include "IMachine.hpp"

IMachine::IMachine(World* world, std::string name, int count)
	: IPlaceable(world, name, count)
{
}

IMachine::~IMachine()
{
}
