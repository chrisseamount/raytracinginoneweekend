#include <iostream>
#include <fstream>
#include <random>
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

double rand_num()
{
	return (rand() / (RAND_MAX + 1.0));
}

hitable* random_scene()
{
	int n = 500;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			double choose_mat = rand_num();
			vec3 center(a + 0.9 * rand_num(), 0.2, b + 0.9 * rand_num());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(rand_num() * rand_num(), rand_num() * rand_num(), rand_num() * rand_num())));
				}
				else if (choose_mat < 0.95)
				{
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+rand_num()), 0.5 * (1 + rand_num()), 0.5 * (1 + rand_num())), 0.5 * rand_num()));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}


vec3 color(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, DBL_MAX,rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	std::ofstream myfile("coolimage.ppm");
	int nx = 1920;
	int ny = 1080;
	int ns = 100;
	myfile << "P3\n" << nx << " " << ny << "\n255\n";
	
	hitable* world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	double dist_to_focus = 10.0;
	double aperture = 0.1;
	camera cam(lookfrom, lookat, vec3(0,1,0), 20, double(nx)/double(ny), aperture, dist_to_focus,0,1);
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
				col += color(r, world,0);
			}
			col /= double(ns);
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			int ir = int(255.99*col.x);
			int ig = int(255.99*col.y);
			int ib = int(255.99*col.z);
			myfile << ir << " " << ig << " " << ib << "\n";
		}
		std::cout << j << " ";
	}
}