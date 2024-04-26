#pragma once


class IPipe : public IPlaceable, public IWorkable
{
public:
	IPipe(World* world, const ItemPipePrefab* prefab, int count);
	virtual ~IPipe();

	virtual void OnPlace() override;
	virtual void OnPickup() override;
	virtual void EarlyUpdate() override;
	virtual void OnComplete() override;
	virtual void LateUpdate() override;

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
