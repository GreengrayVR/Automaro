#include "pch.hpp"
#include "Object.hpp"

Object::~Object()
{
}

Object::Object(World* world, bool solid)
	: m_bSolid(solid)
	, m_pWorld(world)
{
}

World* Object::GetWorld() const
{
	return m_pWorld;
}

bool Object::IsSolid()
{
	return m_bSolid;
}

const Transform& Object::GetTransform() const
{
	return m_Transform;
}

void Object::AddComponent(std::unique_ptr<IComponent>&& component)
{
	components.push_back(std::move(component));
}
