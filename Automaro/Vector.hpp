#pragma once

struct Vector
{
	int x, y;

	Vector();

	Vector(int _x, int _y);

	friend bool operator== (const Vector& lhs, const Vector& rhs);
	void operator += (const Vector& other);
};
