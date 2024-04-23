#pragma once

enum class PipeDirection
{
	UP, DOWN, LEFT, RIGHT
};

class IPipe : public IMachine
{
public:
	IPipe(World* world, float transferSpeed);
	virtual ~IPipe();

	void OnPlace() override;
	void EarlyUpdate() override;
	void OnComplete() override;
	void LateUpdate() override;

private:
	void SetRepresentation(char value);

	ViewASCII* m_View;
	std::map<PipeDirection, std::unique_ptr<Item>> m_Outputs;
	std::map<PipeDirection, std::unique_ptr<Item>> m_Inputs;

	const std::vector<PipeDirection> GetDirections() const;
	const std::vector<PipeDirection> m_vDirections = {
		PipeDirection::UP,
		PipeDirection::DOWN,
		PipeDirection::LEFT,
		PipeDirection::RIGHT
	};
	const std::map<PipeDirection, Vector> m_mDirections = {
		{ PipeDirection::UP, Vector(0, -1) },
		{ PipeDirection::DOWN, Vector(0, -1) },
		{ PipeDirection::LEFT, Vector(0, -1) },
		{ PipeDirection::RIGHT, Vector(0, -1) },
	};
};
