#include "pch.hpp"
#include "ItemPipe.hpp"

ItemPipe::ItemPipe(World* world, int count)
	: IPipe(world, &ItemPipePrefab_ItemPipe, count)
{
}

std::unique_ptr<Item> ItemPipe::Clone() const
{
	return std::make_unique<std::decay_t<decltype(*this)>>(*this);
}
