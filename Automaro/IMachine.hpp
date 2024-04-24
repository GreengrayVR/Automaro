#pragma once

class IMachine : public IPlaceable, public IWorkable
{
public:
	IMachine(World* world, std::string name, int count, int completeTime);
	virtual ~IMachine();

};
