#include "pch.hpp"
#include "Renderer.hpp"


void Write(CMDGraphics::Frame& frame, const std::string& text)
{
	frame.Write(text.c_str());
}

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
	Write(frame, (std::stringstream() << "FPS: " << int(1.f / deltaTime) << "\n\n").str());
	return true;
}

bool Renderer::DrawPopup(CMDGraphics::Frame& frame, World& world, float deltaTime) const
{
	const auto& popupManager = world.GetGame()->GetPopupManager();

	const auto& textToShow = popupManager.GetTextToShow();

	if (!popupManager.IsVisible()) return true;

	std::stringstream draw_text;
	draw_text << "Popup:\n";

	for (const auto& text : textToShow)
	{
		draw_text << text.first << " (" << std::format("{:.2f}", text.second) << " sec)" << '\n';
	}
	draw_text << "\n\n";
	Write(frame, draw_text.str());
	return true;
}

bool Renderer::DrawTerrain(CMDGraphics::Frame& frame, World& world) const
{
	std::stringstream draw_text;
	draw_text << "Keys:\n";
	draw_text << "WASD: Move | Q: Pickup | E: Inventory\n\n";

	Map& map = world.GetMap();


	for (int y = 0; y < map.GetHeight(); y++)
	{
		draw_text << "\n";

		for (int x = 0; x < map.GetWdith(); x++)
		{
			std::vector<std::unique_ptr<Object>>& objects = map.GetObjectsInCell({x, y});

			if (objects.size() == 0)
			{
				draw_text << "_";
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

				draw_text << representation;
			}
		}
	}
	draw_text << "\n\n";
	Write(frame, draw_text.str());
	return true;
}

bool Renderer::DrawTooltip(CMDGraphics::Frame& frame, World& world) const
{
	Map& map = world.GetMap();
	const Vector& pos = world.GetPlayer()->GetTransform().GetPosition();
	ObjectIterator<Item> it = map.GetObjectIteratorInCell<Item>(pos);

	bool drawed = false;

	std::stringstream draw_text;
	while (it.Next())
	{
		if (!drawed)
			draw_text << "You are looking at:\n";
		
		draw_text << it.Get()->GetName() << " [" << it.Get()->GetCount() << "]" << (it.Get()->IsPlaceable() ? " [M]" : "") << "\n";
		drawed = true;
	}

	if (drawed) draw_text << "\n\n";
	Write(frame, draw_text.str());
	return true;
}

bool Renderer::DrawInventory(CMDGraphics::Frame& frame, World& world) const
{
	Inventory& inventory = world.GetPlayer()->GetInventory();
	if (!inventory.IsVisible()) return false;

	auto& items = inventory.GetItems();
	auto selected = inventory.GetSelected();

	std::stringstream draw_text;
	draw_text << "Keys:\n";
	draw_text << "W: Up | S: Down | D: Drop | C: Exit | A: Place Machine\n\n";

	draw_text << "Inventory " << inventory.GetItems().size() << " item(s):\n\n";


	for (int i = 0; i < items.size(); i++)
	{
		if (selected.first == i)
			draw_text << "> ";

		draw_text << items[i]->GetName() << " [" << items[i]->GetCount() << "]" << (items[i]->IsPlaceable() ? " [M]" : "") << "\n";
	}
	draw_text << "\n\n";
	Write(frame, draw_text.str());
	return true;
}
