#ifndef VEC3_H_INCLUDED
#define VEC3_H_INCLUDED

#include <iostream>
#include <cmath>

class vec3
{
public:
	double x, y, z;

	constexpr vec3() noexcept :x(0.0), y(0.0), z(0.0) {}
	constexpr vec3(double _x, double _y, double _z) noexcept :x(_x), y(_y), z(_z) {}

	constexpr const vec3& operator+() const noexcept { return *this; }
	constexpr vec3 operator-() const noexcept { return vec3(-x, -y, -z); };

	constexpr vec3& operator+=(const vec3& v2) noexcept
	{
		x += v2.x;
		y += v2.y;
		z += v2.z;
		return *this;
	}

	constexpr vec3& operator-=(const vec3& v2) noexcept
	{
		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		return *this;
	}

	constexpr vec3& operator*=(const vec3& v2) noexcept
	{
		x *= v2.x;
		y *= v2.y;
		z *= v2.z;
		return *this;
	}

	constexpr vec3& operator/=(const vec3& v2) noexcept
	{
		x /= v2.x;
		y /= v2.y;
		z /= v2.z;
		return *this;
	}

	constexpr vec3& operator*=(const double t) noexcept
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	constexpr vec3& operator/=(const double t) noexcept
	{
		double k = 1.0 / t;

		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	double length() const noexcept
	{
		return sqrt(x * x + y * y + z * z);
	}

	constexpr double squared_length() const noexcept
	{
		return x * x + y * y + z * z;
	}

	void make_unit_vector() noexcept
	{
		double k = 1.0 / sqrt(x * x + y * y + z * z);
		x *= k;
		y *= k;
		z *= k;
	}
};

std::istream& operator>>(std::istream &is, vec3 &t) noexcept
{
	is >> t.x >> t.y >> t.z;
	return is;
}

std::ostream& operator<<(std::ostream &os, const vec3 &t) noexcept
{
	os << t.x << " " << t.y << " " << t.z;
	return os;
}

constexpr vec3 operator+(const vec3 &v1, const vec3 &v2) noexcept
{
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

constexpr vec3 operator-(const vec3 &v1, const vec3 &v2) noexcept
{
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

constexpr vec3 operator*(const vec3 &v1, const vec3 &v2) noexcept
{
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

constexpr vec3 operator/(const vec3 &v1, const vec3 &v2) noexcept
{
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

constexpr vec3 operator*(double t, const vec3 &v) noexcept
{
	return vec3(v.x * t, v.y * t, v.z * t);
}

constexpr vec3 operator/(vec3 v, double t) noexcept
{
	return vec3(v.x / t, v.y / t, v.z / t);
}

constexpr vec3 operator*(const vec3 &v, double t) noexcept
{
	return vec3(t*v.x, t*v.y, t*v.z);
}

constexpr double dot(const vec3 &v1, const vec3 &v2) noexcept
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

constexpr vec3 cross(const vec3 &v1, const vec3 &v2) noexcept
{
	return vec3((v1.y*v2.z - v1.z*v2.y),
				   (-(v1.x*v2.z - v1.z*v2.x)),
				   (v1.x*v2.y - v1.y*v2.x));
}

constexpr vec3 unit_vector(vec3 v) noexcept
{
	return v / v.length();
}

#endif // !VEC3_H_INCLUDED