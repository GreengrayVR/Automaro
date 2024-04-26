#pragma once

using TextToShow = std::vector<std::pair<std::string, float>>;

class PopupManager
{
public:
	PopupManager();

	void ShowText(const std::string& text, float time = 3.f);
	void Update(float deltaTime);
	bool IsVisible() const;

	const TextToShow& GetTextToShow() const;

private:
	TextToShow m_vTextToShow;
	bool m_bIsVisible = false;

};
