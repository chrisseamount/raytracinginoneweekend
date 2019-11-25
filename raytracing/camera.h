#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "ray.h"
#include <cmath>

vec3 random_in_unit_disk()
{
	vec3 p;
	do {
		p = 2.0 * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)),0) - vec3(1,1,0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
public:
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	vec3 u, v, w;
	double time0, time1;
	double lens_radius;

	ray get_ray(double s, double t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x + v * rd.y;
		double time = time0 + (rand() / (RAND_MAX + 1.0)) * (time1 - time0);
		return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
	}
	
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperature, double focus_dist, double t0, double t1)
	{
		time0 = t0;
		time1 = t1;
		lens_radius = aperature / 2;
		double theta = vfov * std::_Pi / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}
};

#endif // !CAMERA_H_INCLUDED