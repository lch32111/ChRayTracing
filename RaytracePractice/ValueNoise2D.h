#pragma once
#ifndef __VALUE_NOISE_2D_H__
#define __VALUE_NOISE_2D_H__

#include <random> 
#include <functional> 

#include <glm/glm.hpp>

#include "noiseUtil.h"

class ValueNoise2D
{
public:
	ValueNoise2D(unsigned seed = 2011)
	{
		std::mt19937 gen(seed);
		std::uniform_real_distribution<float> distrFloat;
		auto randFloat = std::bind(distrFloat, gen);

		// create an array of random values and initialize permutation table
		for (unsigned i = 0; i < kMaxTableSize; ++i)
		{
			r[i] = randFloat();
			permutationTable[i] = i;
		}

		// shuffle values of the permutation table
		std::uniform_int_distribution<unsigned> distrUInt;
		auto randUInt = std::bind(distrUInt, gen);
		for (unsigned i = 0; i < kMaxTableSize; ++i)
		{
			unsigned k = randUInt() & kMaxTableSizeMask;
			std::swap(permutationTable[i], permutationTable[k]);
			permutationTable[i + kMaxTableSize] = permutationTable[i];
		}
	}

	// Evaluate the noise function at position x
	float eval(const glm::vec2& p)
	{
		int xi = std::floor(p.x);
		int yi = std::floor(p.y);

		int rx0 = xi & kMaxTableSizeMask;
		int rx1 = (rx0 + 1) & kMaxTableSizeMask;
		int ry0 = yi & kMaxTableSizeMask;
		int ry1 = (ry0 + 1) & kMaxTableSizeMask;

		// random values at the corners of the cell using permutation table
		const float& c00 = r[permutationTable[permutationTable[rx0] + ry0]];
		const float& c10 = r[permutationTable[permutationTable[rx1] + ry0]];
		const float& c01 = r[permutationTable[permutationTable[rx0] + ry1]];
		const float& c11 = r[permutationTable[permutationTable[rx1] + ry1]];

		// remapping of tx and ty using Smoothstep function;
		float tx = p.x - xi;
		float ty = p.y - yi;
		float sx = smoothStep(tx);
		float sy = smoothStep(ty);

		// linearly interpolate values along the x axis
		float nx0 = lerp(c00, c10, sx);
		float nx1 = lerp(c01, c11, sx);

		// linearly interpolate the nx0/nx1 along the y axis
		return lerp(nx0, nx1, sy);
	}

	static const unsigned kMaxTableSize = 256;
	static const unsigned kMaxTableSizeMask = kMaxTableSize - 1;
	float r[kMaxTableSize];
	unsigned permutationTable[kMaxTableSize * 2];
};

#endif