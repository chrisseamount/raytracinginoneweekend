#include <iostream>
#include <fstream>
#include <random>
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"


vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001, DBL_MAX,rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(ray(rec.p,target - rec.p), world);
	}
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5*(unit_direction.y + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream myfile("first.ppm");
	int nx = 400;
	int ny = 200;
	int ns = 200;
	myfile << "P3\n" << nx << " " << ny << "\n255\n";
	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0,0,0);
			for (int s = 0; s < ns; s++)
			{
				double u = double(i + (rand() / (RAND_MAX + 1.0))) / double(nx);
				double v = double(j + (rand() / (RAND_MAX + 1.0))) / double(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= double(ns);
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			int ir = int(255.99*col.x);
			int ig = int(255.99*col.y);
			int ib = int(255.99*col.z);
			myfile << ir << " " << ig << " " << ib << "\n";
		}
	}
}