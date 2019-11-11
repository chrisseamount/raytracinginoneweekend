#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "hitable.h"

class sphere : public hitable
{
public:
	vec3 center;
	double radius;

	sphere(vec3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const
	{
		vec3 oc = r.origin() - center;
		double a = dot(r.direction(), r.direction());
		double b = dot(oc, r.direction());
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - a * c;
		if (discriminant > 0)
		{
			double temp = (-b - sqrt(discriminant)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
		}
		return false;
	}
};

#endif // !SPHERE_H_INCLUDED