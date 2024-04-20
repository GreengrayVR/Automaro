#pragma once

class World;

class Object
{
public:
	virtual ~Object();

	Object(World* world, bool solid = false);

	template <typename T>
	T* FindComponent()
	{
		for (auto& component : components)
			if (auto c = dynamic_cast<T*>(component.get()))
				return c;

		return nullptr;
	}

	World* GetWorld() const;
	bool IsSolid();
	const Transform& GetTransform() const;

protected:
	void AddComponent(std::unique_ptr<IComponent>&& component);

private:
	Transform m_Transform;
	bool m_bSolid;
	World* m_pWorld;
	std::vector<std::unique_ptr<IComponent>> components;
};
