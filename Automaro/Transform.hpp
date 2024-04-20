#pragma once

class Transform
{
public:
	const Vector& GetPosition() const;

	void SetPosition(const Vector& pos);

	void SetLocalPosition(const Vector& pos);

private:
	Vector m_vPosition;
};
