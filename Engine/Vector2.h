#pragma once

#include <cmath>
#include <cassert>

namespace ChiefEngine {
	class Vector2 {
	public:
		float x, y;

		Vector2() = default;
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}

		float operator [] (unsigned int index) const { assert(index < 2); return (index == 0) ? x : y; }
		float& operator [] (unsigned int index) { assert(index < 2); return (index == 0) ? x : y; }

		bool operator == (const Vector2& other) const { return(this->x == other.x) && (this->y == other.y); }
		bool operator != (const Vector2& other) const { return(this->x != other.x) || (this->y != other.y); }

		float GetX() const { return this->x; }
		float GetY() const { return this->y; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return std::sqrt(LengthSqr()); }

		float Distance(const Vector2& other) const { return (other - *this).Length(); }

		float Dot(const Vector2& other) const { return (this->x * other.x) + (this->y * other.y); }
		float AngleBetween(const Vector2& other) const { return std::acos(Dot(other)); }
		float Angle() const { return std::atan2(this->y, this->x); }

		Vector2 Rotate(float radians) const {
			Vector2 temp = { 0.0f };
			temp.x = this->x * std::cos(radians) - this->y * std::sin(radians);
			temp.y = this->x * std::sin(radians) + this->y * std::cos(radians);
			return temp;
		}

		Vector2 Normalized() const { return *this/Length(); }

		Vector2 operator+(const Vector2& other) const { return Vector2(this->x + other.x, this->y + other.y); }
		Vector2 operator-(const Vector2& other) const { return Vector2(this->x - other.x, this->y - other.y); }
		Vector2 operator*(const Vector2& other) const { return Vector2(this->x * other.x, this->y * other.y); }
		Vector2 operator/(const Vector2& other) const { return Vector2(this->x / other.x, this->y / other.y); }

		Vector2 operator+(float val) const { return Vector2(this->x + val, this->y + val); }
		Vector2 operator-(float val) const { return Vector2(this->x - val, this->y - val); }
		Vector2 operator*(float val) const { return Vector2(this->x * val, this->y * val); }
		Vector2 operator/(float val) const { return Vector2(this->x / val, this->y / val); }

		Vector2& operator+=(const Vector2& other) { this->x += other.x; this->y += other.y; return *this; }
		Vector2& operator-=(const Vector2& other) { this->x -= other.x; this->y -= other.y; return *this; }
		Vector2& operator*=(const Vector2& other) { this->x *= other.x; this->y *= other.y; return *this; }
		Vector2& operator/=(const Vector2& other) { this->x /= other.x; this->y /= other.y; return *this; }

		Vector2& operator+=(float val) { this->x += val; this->y += val; return *this; }
		Vector2& operator-=(float val) { this->x -= val; this->y -= val; return *this; }
		Vector2& operator*=(float val) { this->x *= val; this->y *= val; return *this; }
		Vector2& operator/=(float val) { this->x /= val; this->y /= val; return *this; }
	};
}