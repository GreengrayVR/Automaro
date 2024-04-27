#pragma once

enum class Direction : int
{
	UP, DOWN, LEFT, RIGHT
};

class ItemIOContainer
{
public:
	ItemIOContainer() = default;
	ItemIOContainer(const ItemIOContainer& other);

	std::unique_ptr<Item> m_ItemOutput;
	std::unique_ptr<Item> m_ItemInput;
};

class IWorkable : protected ItemIOContainer
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

	std::unique_ptr<Item> TransferInput();
	std::unique_ptr<Item> TransferOutput();
	bool TransferOutput(int count);
	
	Item* GetItemInput();
	Item* GetItemOutput();
	void SetItemInput(std::unique_ptr<Item> input);

	void SetInput(IWorkable* output);
	void SetOutput(IWorkable* output);

	IWorkable* GetOutput();

protected:

	IWorkable* m_Output;
	IWorkable* m_Input;
	std::vector<Direction> m_vDirectionOutput;

private:
	float m_fTimeToComplete;
	float m_fTime;
	bool m_bIsRunning;

	World* m_pWorld;
};
