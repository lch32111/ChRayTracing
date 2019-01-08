#pragma once
#ifndef __VALUE_NOISE_1D_H__
#define __VALUE_NOISE_1D_H__

#include "noiseUtil.h"
#include "GPED_random.h"

class ValueNoise1D
{
public:
	ValueNoise1D(unsigned seed = 2011)
	{
		GPED::Random rand(seed);

		for (unsigned i = 0; i < kMaxVertices; ++i)
			r[i] = rand.randomReal();
	}

	// Evaluate the noise function at position x
	float eval(const float& x)
	{
		// Floor
		int xi = (int)x - (x < 0 && x != (int)x);
		float t = x - xi;

		// Modulo using &
		int xMin = xi & kMaxVerticesMask;
		int xMax = (xMin + 1) & kMaxVerticesMask;

		// return lerp(r[xMin], r[xMax], t);
		// return consineRemap(r[xMin], r[xMax], t);
		return smoothstepRemap(r[xMin], r[xMax], t);
	}

	static const unsigned kMaxVertices = 256;
	static const unsigned kMaxVerticesMask = kMaxVertices - 1;
	float r[kMaxVertices];
};

#endif