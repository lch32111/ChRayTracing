#pragma once
#ifndef __RC_HITABLE_H__
#define __RC_HITABLE_H__

#include <glm/glm.hpp>

#include "ray.h"

struct rcHit_record
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

class rcHitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, rcHit_record& rec) const = 0;
};

#endif
