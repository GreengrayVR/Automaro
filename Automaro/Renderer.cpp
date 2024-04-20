#include "pch.hpp"
#include "Renderer.hpp"

void cls()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// draw_text uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// draw_text entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

std::stringstream draw_text;
void Renderer::Draw(World& world, float deltaTime) const
{
	cls();

	DrawDebug(world, deltaTime);
	if (DrawInventory(world))
	{
		DrawPopup(world, deltaTime);

		std::cout << draw_text.str();
		draw_text.str("");
		return;
	}
	DrawTerrain(world);
	DrawPopup(world, deltaTime);
	DrawTooltip(world);

	std::cout << draw_text.str();
	draw_text.str("");
}

bool Renderer::DrawDebug(World& world, float deltaTime) const
{
	draw_text << "FPS: " << int(1.f / deltaTime)  << "\n\n";
	return true;
}

bool Renderer::DrawPopup(World& world, float deltaTime) const
{
	const auto& popupManager = world.GetGame()->GetPopupManager();

	const auto& textToShow = popupManager.GetTextToShow();

	if (!popupManager.IsVisible()) return true;

	draw_text << "Popup:\n";

	for (const auto& text : textToShow)
	{
		draw_text << text.first << " (" << std::format("{:.2f}", text.second) << " sec)" << '\n';
	}
	draw_text << "\n\n";

	return true;
}

bool Renderer::DrawTerrain(World& world) const
{
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
				int tempPriority = -9999999999;
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
	return true;
}

bool Renderer::DrawTooltip(World& world) const
{
	Map& map = world.GetMap();
	const Vector& pos = world.GetPlayer()->GetTransform().GetPosition();
	ObjectIterator<Item> it = map.GetObjectIteratorInCell<Item>(pos);

	bool drawed = false;

	while (it.Next())
	{
		if (!drawed)
			draw_text << "You are looking at:\n";
		
		DrawItem(it.Get());

		drawed = true;
	}

	if (drawed) draw_text << "\n\n";
	
	return true;
}

bool Renderer::DrawInventory(World& world) const
{
	Inventory& inventory = world.GetPlayer()->GetInventory();
	if (!inventory.IsVisible()) return false;

	auto& items = inventory.GetItems();
	auto selected = inventory.GetSelected();

	draw_text << "Keys:\n";
	draw_text << "W: Up | S: Down | D: Drop | C: Exit | A: Place Machine\n\n";

	draw_text << "Inventory " << inventory.GetItems().size() << " item(s):\n\n";


	for (int i = 0; i < items.size(); i++)
	{
		if (selected.first == i)
			draw_text << "> ";

		DrawItem(items[i].get());

	}
	draw_text << "\n\n";

	return true;
}

void Renderer::DrawItem(Item* item) const
{
	draw_text << item->GetName() << " [" << item->GetCount() << "]" << (item->IsPlaceable() ? " [M]" : "") << "\n";
}
