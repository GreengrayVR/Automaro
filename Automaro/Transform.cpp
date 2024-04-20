#include "pch.hpp"
#include "Transform.hpp"

const Vector& Transform::GetPosition() const
{
	return m_vPosition;
}

void Transform::SetPosition(const Vector& pos)
{
	m_vPosition = pos;
}

void Transform::SetLocalPosition(const Vector& pos)
{
	m_vPosition.x += pos.x;
	m_vPosition.y += pos.y;
}
