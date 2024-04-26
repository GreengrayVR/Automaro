#pragma once

class ItemPipe : public IPipe
{
public:
	ItemPipe(World* world, int count);

	std::unique_ptr<Item> Clone() const;
};