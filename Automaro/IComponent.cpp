#include "pch.hpp"
#include "IComponent.hpp"

ComponentContainer::ComponentContainer(const ComponentContainer& other)
{
    for (auto& comp : other.components)
        components.push_back(comp->Clone());
}

IComponent::~IComponent()
{
}
