#include "pch.hpp"
#include "Vector.hpp"

Vector::Vector()
	: x(0), y(0)
{
}

Vector::Vector(int _x, int _y)
	: x(_x), y(_y)
{
}

Vector& Vector::operator+=(const Vector& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(*this) += other;
}

Vector Vector::Down()
{
	return Vector(0, 1);
}

Vector Vector::Up()
{
	return Vector(0, -1);
}

Vector Vector::Left()
{
	return Vector(-1, 0);
}

Vector Vector::Right()
{
	return Vector(1, 0);
}

bool operator==(const Vector& lhs, const Vector& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
