#pragma once

using TextToShow = std::vector<std::pair<std::string, float>>;

class PopupManager
{
public:
	PopupManager();

	void ShowText(const std::string& text);
	void Update(float deltaTime);
	bool IsVisible() const;

	const TextToShow& GetTextToShow() const;

private:
	TextToShow m_vTextToShow;
	const float POPUP_END_TIME = 3.f;
	bool m_bIsVisible = false;

};
