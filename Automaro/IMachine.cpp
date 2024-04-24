#include "pch.hpp"
#include "IMachine.hpp"

IMachine::IMachine(World* world, std::string name, int count, int completeTime)
	: IPlaceable(world, name, count)
	, IWorkable(world, completeTime)
{
}

IMachine::~IMachine()
{
}
