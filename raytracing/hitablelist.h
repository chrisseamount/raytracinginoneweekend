#ifndef HITABLELIST_H_INCLUDED
#define HITABLELIST_H_INCLUDED

#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable** list;
	int list_size;
	
	hitable_list(hitable** l, int n) { list = l; list_size = n; }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const
	{
		hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (int i = 0; i < list_size; i++)
		{
			if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
};

#endif // !HITABLELIST_H_INCLUDED