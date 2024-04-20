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

void Vector::operator+=(const Vector& other)
{
	x += other.x;
	y += other.y;
}

bool operator==(const Vector& lhs, const Vector& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
