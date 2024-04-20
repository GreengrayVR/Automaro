#pragma once

class Renderer
{
public:

	void Draw(World& world, float deltaTime) const;

private:
	bool DrawDebug(World& world, float deltaTime) const;
	bool DrawPopup(World& world, float deltaTime) const;
	bool DrawTerrain(World& world) const;
	bool DrawTooltip(World& world) const;
	bool DrawInventory(World& world) const;

	void DrawItem(Item* item) const;
};
