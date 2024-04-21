#include "pch.hpp"
#include "Renderer.hpp"

void Renderer::Draw(World& world, float deltaTime)
{
	CMDGraphics::Frame frame(m_Gfx);

	DrawDebug(frame, world, deltaTime);
	if (DrawInventory(frame, world))
	{
		DrawPopup(frame, world, deltaTime);
		return;
	}
	DrawTerrain(frame, world);
	DrawPopup(frame, world, deltaTime);
	DrawTooltip(frame, world);
}

bool Renderer::DrawDebug(CMDGraphics::Frame& frame, World& world, float deltaTime) const
{
	frame.WriteF("FPS: {}\n\n", int(1.f / deltaTime));
	return true;
}

bool Renderer::DrawPopup(CMDGraphics::Frame& frame, World& world, float deltaTime) const
{
	const auto& popupManager = world.GetGame()->GetPopupManager();

	const auto& textToShow = popupManager.GetTextToShow();

	if (!popupManager.IsVisible()) return true;

	frame.WriteF("Popup:\n");

	for (const auto& text : textToShow)
		frame.WriteF("{} ({:.2f} sec)\n", text.first, text.second);

	frame.WriteF("\n\n");
	return true;
}

bool Renderer::DrawTerrain(CMDGraphics::Frame& frame, World& world) const
{
	frame.WriteF("Keys:\n");
	frame.WriteF("WASD: Move | Q: Pickup | E: Inventory\n\n");

	Map& map = world.GetMap();


	for (int y = 0; y < map.GetHeight(); y++)
	{
		frame.WriteF("\n");

		for (int x = 0; x < map.GetWdith(); x++)
		{
			std::vector<std::unique_ptr<Object>>& objects = map.GetObjectsInCell({x, y});

			if (objects.size() == 0)
			{
				frame.WriteF("_");
			}
			else
			{
				int tempPriority = -9999;
				char representation = '.';

				for (size_t i = 0; i < objects.size(); i++)
				{
					auto* view = objects[i]->FindComponent<ViewASCII>();
					if (view->GetPriority() > tempPriority)
					{
						tempPriority = view->GetPriority();
						representation = view->GetRepresentation();
					}
				}

				frame.Write(representation);
			}
		}
	}
	frame.WriteF("\n\n");
	return true;
}

bool Renderer::DrawTooltip(CMDGraphics::Frame& frame, World& world) const
{
	Map& map = world.GetMap();
	const Vector& pos = world.GetPlayer()->GetTransform().GetPosition();
	ObjectIterator<Item> it = map.GetObjectIteratorInCell<Item>(pos);

	bool drawed = false;

	
	while (it.Next())
	{
		if (!drawed)
			frame.WriteF("You are looking at:\n");
		
		frame.WriteF(
			"{} [{}] {}\n", 
			it.Get()->GetName(), 
			it.Get()->GetCount(), 
			(it.Get()->IsPlaceable() ? " [M]" : "")
		);
		drawed = true;
	}

	if (drawed) frame.WriteF("\n\n");
	return true;
}

bool Renderer::DrawInventory(CMDGraphics::Frame& frame, World& world) const
{
	Inventory& inventory = world.GetPlayer()->GetInventory();
	if (!inventory.IsVisible()) return false;

	auto& items = inventory.GetItems();
	auto selected = inventory.GetSelected();
	
	frame.WriteF("Keys:\n");
	frame.WriteF("W: Up | S: Down | D: Drop | C: Exit | A: Place Machine\n\n");

	frame.WriteF("Inventory {} item(s):\n\n", inventory.GetItems().size());

	for (int i = 0; i < items.size(); i++)
	{
		if (selected.first == i)
			frame.WriteF("> ");

		frame.WriteF(
			"{} [{}] {}\n",
			items[i]->GetName(),
			items[i]->GetCount(),
			(items[i]->IsPlaceable() ? " [M]" : "")
		);
	}
	frame.WriteF("\n\n");
	return true;
}
