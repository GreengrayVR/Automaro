#pragma once

class Renderer
{
public:

	void Draw(World& world, float deltaTime);

private:
	bool DrawDebug(CMDGraphics::Frame& frame, World& world, float deltaTime) const;
	bool DrawPopup(CMDGraphics::Frame& frame, World& world, float deltaTime) const;
	bool DrawTerrain(CMDGraphics::Frame& frame, World& world) const;
	bool DrawTooltip(CMDGraphics::Frame& frame, World& world) const;
	bool DrawInventory(CMDGraphics::Frame& frame, World& world) const;
	
	CMDGraphics::Graphics m_Gfx;
};
