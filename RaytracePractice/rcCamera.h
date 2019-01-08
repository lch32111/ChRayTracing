#pragma once
#ifndef __RC_CAMERA_H__
#define __RC_CAMERA_H__

#include "ray.h"

class rcCamera
{
public:
	rcCamera()
		:
		lower_left_corner(glm::vec3(-2, -1, -1)),
		horizontal(glm::vec3(4.0, 0.0, 0.0)),
		vertical(glm::vec3(0.0, 2.0, 0.0)),
		origin(glm::vec3(0.0))
	{ 	}

	ray get_ray(float u, float v)
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};

#endif
