#pragma once
#ifndef __RC_SPHERE_H__
#define __RC_SPHERE_H__

#include "rcHitable.h"

class rcSphere : public rcHitable
{
public:
	rcSphere() { }
	rcSphere(glm::vec3 cen, float r)
		: center(cen), radius(r)
	{ }

	virtual bool hit(const ray& r, float t_min, float t_max, rcHit_record& rec) const;

	glm::vec3 center;
	float radius;
};

bool rcSphere::hit(const ray& r, float t_min, float t_max, rcHit_record& rec) const
{
	glm::vec3 m = r.origin() - center;
	float b = glm::dot(m, r.direction());
	float c = glm::dot(m, m) - radius * radius;
	if (c > 0.0 && b > 0.0) return false;
	float discr = b * b - c;
	if (discr < 0.0) return false;
	
	float t1 = -b - sqrtf(discr);
	
	if (t_min < t1  && t1 < t_max)
	{
		rec.t = t1;
		rec.p = r.point_at_parameter(t1);
		rec.normal = (rec.p - center) * (1.f / radius);
		return true;
	}

	float t2 = -b + sqrtf(discr);
	if (t_min < t2 && t2 < t_max)
	{
		rec.t = t2;
		rec.p = r.point_at_parameter(t2);
		rec.normal = (rec.p - center) * (1.f / radius);
		return true;
	}

	return false;
}

#endif
