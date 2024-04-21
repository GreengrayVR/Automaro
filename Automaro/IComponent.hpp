#pragma once

class IComponent
{
public:
    virtual ~IComponent();

    virtual std::unique_ptr<IComponent> Clone() const = 0;
};

class ComponentContainer
{
public:
    std::vector<std::unique_ptr<IComponent>> components;

	ComponentContainer() = default;
    ComponentContainer(const ComponentContainer& other);

	template <typename T>
	T* FindComponent()
	{
		for (auto& component : components)
			if (auto c = dynamic_cast<T*>(component.get()))
				return c;

		return nullptr;
	}
};
