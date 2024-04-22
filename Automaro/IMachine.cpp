#include "pch.hpp"
#include "IMachine.hpp"

IMachine::IMachine(World* world, std::string name, int count, int completeTime)
	: IPlaceable(world, name, count)
	, m_fTimeToComplete(completeTime)
	, m_fTime(completeTime)
	, m_bIsRunning(false)
{
}

IMachine::~IMachine()
{
}

void IMachine::Update(float deltaTime)
{
	EarlyUpdate();

	if (!IsRunning()) return;

	m_fTime -= deltaTime;
	if (m_fTime < 0)
	{
		OnComplete();
		m_fTime = m_fTimeToComplete;
	}

	LateUpdate();
}

float IMachine::GetTime() const
{
	return m_fTime;
}

float IMachine::GetTimeToComplete() const
{
	return m_fTimeToComplete;
}

void IMachine::SetRunning(bool running)
{
	m_bIsRunning = running;

	if (!m_bIsRunning)
	{
		m_fTime = m_fTimeToComplete;
	}

	SetPickupable(!m_bIsRunning);
}

bool IMachine::IsRunning() const
{
	return m_bIsRunning;
}
