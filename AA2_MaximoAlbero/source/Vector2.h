#pragma once
#include <math.h>

class Vector2 {
public:
	float x;
	float y;
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	void Normalize() {
		float length = sqrtf(x * x + y * y);
		x /= length;
		y /= length;
	}

	Vector2 const operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 const operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 const operator*(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 const operator*(const float& other) const {
		return Vector2(x * other, y * other);
	}

	Vector2 const operator/(const float& other) const {
		return Vector2(x / other, y / other);
	}

	Vector2 const operator!() {
		Normalize();
		return *this;
	}
};