#pragma once

class World;

class Object : public ComponentContainer
{
public:
	virtual ~Object();

	Object(World* world, bool solid = false);

	World* GetWorld() const;
	bool IsSolid();
	const Transform& GetTransform() const;

protected:
	void AddComponent(std::unique_ptr<IComponent>&& component);

private:
	Transform m_Transform;
	bool m_bSolid;
	World* m_pWorld;
};
