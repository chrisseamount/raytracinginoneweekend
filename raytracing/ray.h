#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "vec3.h"

class ray
{
public:
	vec3 A;
	vec3 B;
	double _time = 0.0;
	
	constexpr ray() noexcept {};
	constexpr ray(const vec3& a, const vec3& b, double ti) noexcept { A = a; B = b; _time = ti; }
	constexpr vec3 origin() const noexcept { return A; }
	constexpr vec3 direction() const noexcept { return B; }
	constexpr double time() const noexcept { return _time; }
	constexpr vec3 point_at_parameter(double t) const noexcept { return A + t * B; }
};

#endif // !RAY_H_INCLUDED