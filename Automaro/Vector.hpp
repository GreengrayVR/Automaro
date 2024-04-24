#pragma once

struct Vector
{
	int x, y;

	Vector();

	Vector(int _x, int _y);

	friend bool operator== (const Vector& lhs, const Vector& rhs);
	Vector& operator += (const Vector& other);
	Vector operator + (const Vector& other) const;

	static Vector Down();
	static Vector Up();
	static Vector Left();
	static Vector Right();
};
