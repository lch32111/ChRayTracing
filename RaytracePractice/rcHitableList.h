#pragma once
#ifndef __RC_HITABLE_LIST_H__
#define __RC_HITABLE_LIST_H__

#include "rcHitable.h"

class rcHitable_List : public rcHitable
{
public:
	rcHitable_List() { }
	rcHitable_List(rcHitable** l, int n)
		: list(l), list_size(n)
	{ 	}

	virtual bool hit(const ray& r, float t_min, float t_max, rcHit_record& rec) const;

	rcHitable** list;
	int list_size;
};

inline bool rcHitable_List::hit(const ray& r, float t_min, float t_max, rcHit_record& rec) const
{
	rcHit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; ++i)
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

#endif
