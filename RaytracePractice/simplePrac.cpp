#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdio> 
#include <random>
#include <functional>

#include "imageSave.h"
#include "ray.h"

#include "rcSphere.h"
#include "rcHitableList.h"
#include "rcCamera.h"
#include "GPED_random.h"

#include <float.h>

glm::vec3 random_in_unit_sphere()
{
	/*
	GPED::Random rand(324234);
	glm::vec3 p;
	do
	{
		p = 2.f * glm::vec3(rand.randomReal(), rand.randomReal(), rand.randomReal()) - glm::vec3(1);
	} while (glm::dot(p, p) >= 1.0f);
	*/

	/*
	std::mt19937 gen(123456);
	std::uniform_real_distribution<float> distrFloat;
	auto randFloat = std::bind(distrFloat, gen);
	glm::vec3 p;
	do
	{
		p = 2.f * glm::vec3(randFloat(), randFloat(), randFloat()) - glm::vec3(1);
	} 
	while (glm::dot(p, p) >= 1.0f);
	*/
	
	std::mt19937 gen(123456);
	std::uniform_real_distribution<float> distrFloat;
	auto randFloat = std::bind(distrFloat, gen);
	glm::vec3 p;
	p = 2.f * glm::vec3(randFloat(), randFloat(), randFloat()) - glm::vec3(1);
	p = glm::normalize(p);

	/*
	GPED::Random rand(324234);
	glm::vec3 p;
	p = 2.f * glm::vec3(rand.randomReal(), rand.randomReal(), rand.randomReal()) - glm::vec3(1);
	p = glm::normalize(p);
	*/
	return p;
}

glm::vec3 color(const ray& r, rcHitable* world)
{
	rcHit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5f * color(ray(rec.p, target - rec.p), world);
	}
	else
	{
		glm::vec3 unit_direction = r.direction();
		float t = 0.5f * (unit_direction.y + 1.0);
		return (1.f - t) * glm::vec3(1.0) + t * glm::vec3(0.5, 0.7, 1.0);
	}
}

glm::vec3 noRecurColor(const ray& r, rcHitable* world)
{
	rcHit_record rec;
	ray tempRay = r;
	bool recursiveDone = false;

	float t = 0.5f * (r.direction().y + 1.0);
	glm::vec3 resultColor = (1.f - t) * glm::vec3(1.0) + t * glm::vec3(0.5, 0.7, 1.0);

	while (!recursiveDone)
	{
		if (world->hit(tempRay, 0.001, FLT_MAX, rec))
		{
			glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
			tempRay.A = rec.p;
			tempRay.B = glm::normalize(target - rec.p);
			
			resultColor *= 0.5f;
			continue;
		}

		break;
	}

	return resultColor;
}

#define CHANNEL_NUM 3
int main()
{
	const int nx = 200;
	const int ny = 100;
	const int ns = 100;
	float* pixels = new float[nx * ny * CHANNEL_NUM];

	rcHitable* list[2];
	list[0] = new rcSphere(glm::vec3(0, 0, -1), 0.5);
	list[1] = new rcSphere(glm::vec3(0, -100.5, -1), 100);
	rcHitable* world = new rcHitable_List(list, 2);

	rcCamera cam;
	std::mt19937 gen(123456);
	std::uniform_real_distribution<float> distrFloat;
	auto randFloat = std::bind(distrFloat, gen);

	int index = 0;
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			glm::vec3 col(0);
			for (int s = 0; s < ns; ++s)
			{
				float u = float(i + randFloat()) / float(nx);
				float v = float(j + randFloat()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += noRecurColor(r, world);
			}
			
			col /= float(ns);

			pixels[index++] = sqrtf(col.r);
			pixels[index++] = sqrtf(col.g);
			pixels[index++] = sqrtf(col.b);
		}
	}


	savePNGfile(pixels, nx, ny, "noRecurdiffuseRayTracer.png");

	delete[] pixels;
	delete list[0];
	delete list[1];
	delete world;
	return 0;
}
