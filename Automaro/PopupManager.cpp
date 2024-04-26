#include "pch.hpp"
#include "PopupManager.hpp"

PopupManager::PopupManager()
{
}

void PopupManager::ShowText(const std::string& text, float time)
{
	m_vTextToShow.push_back(std::make_pair(text, time));
	m_bIsVisible = true;
}

const TextToShow& PopupManager::GetTextToShow() const
{
	return m_vTextToShow;
}

void PopupManager::Update(float deltaTime)
{
	if (!IsVisible()) return;

	for (auto it = m_vTextToShow.begin(); it != m_vTextToShow.end(); )
	{
		auto& text = *it;

		text.second -= deltaTime;

		if (text.second <= 0)
			it = m_vTextToShow.erase(it);
		else
			++it;
	}

	if (m_vTextToShow.size() == 0)
		m_bIsVisible = false;
}

bool PopupManager::IsVisible() const
{
	return GetTextToShow().size() != 0;
}
