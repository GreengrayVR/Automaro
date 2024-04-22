#pragma once
#include "MachineManager.hpp"

class IMachine : public IPlaceable
{
public:
	IMachine(World* world, std::string name, int count, int completeTime);
	virtual ~IMachine();

	virtual void EarlyUpdate() = 0;
	virtual void OnComplete() = 0;
	virtual void LateUpdate() = 0;
	void Update(float deltaTime) override;
	float GetTime() const;
	float GetTimeToComplete() const;
	void SetRunning(bool running);
	bool IsRunning() const;

private:
	float m_fTimeToComplete;
	float m_fTime;
	bool m_bIsRunning;
};
