#pragma once


class IPipe : public IPlaceable, public IWorkable
{
public:
	IPipe(World* world, float transferSpeed);
	virtual ~IPipe();

	void OnPlace() override;
	void OnPickup() override;
	void EarlyUpdate() override;
	void OnComplete() override;
	void LateUpdate() override;

private:
	void SetRepresentation(char value);

	ViewASCII* m_View;

	const std::map<Direction, Vector> m_Directions = {
		{ Direction::UP, Vector::Up() },
		{ Direction::DOWN, Vector::Down() },
		{ Direction::LEFT, Vector::Left() },
		{ Direction::RIGHT, Vector::Right() },
	};
	
};
