#pragma once

enum class Direction : int
{
	UP, DOWN, LEFT, RIGHT
};

class IWorkable
{
public:
	IWorkable(World* world, int completeTime, Direction outputDir = Direction::UP);
	virtual ~IWorkable();

	void Update(float deltaTime);
	float GetTime() const;
	float GetTimeToComplete() const;
	void SetRunning(bool running);
	bool IsRunning() const;
	void Reset();

	virtual void EarlyUpdate() = 0;
	virtual void OnComplete() = 0;
	virtual void LateUpdate() = 0;

	std::unique_ptr<Item> TransferOutput();
	bool TransferOutput(int count);
	
	Item* GetItemOutput();
	Item* GetItemInput();

	void SetOutput(IWorkable* output);
	void SetInput(std::unique_ptr<Item> input);

	IWorkable* GetOutput();

protected:
	std::unique_ptr<Item> m_ItemOutput;
	std::unique_ptr<Item> m_ItemInput;

	IWorkable* m_Output;
	std::vector<Direction> m_vDirectionOutput;

private:
	float m_fTimeToComplete;
	float m_fTime;
	bool m_bIsRunning;

	World* m_pWorld;
};
