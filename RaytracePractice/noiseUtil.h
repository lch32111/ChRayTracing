#pragma once
#ifndef __NOISE_UTIL_H__
#define __NOISE_UTIL_H__

#include <assert.h>
#include <cmath>

#define mPI 3.14159265358979323846264338327950288
template <class T>
inline T min(const T& a, const T& b) { return (a < b ? a : b); }
template <typename T = float>
inline T lerp(const T& lo, const T& hi, const T& t) { return lo + (hi - lo) * t; }
inline float cosineSmooth(const float& t) { return (1 - std::cosf(t * mPI)) * 0.5f; }
inline float smoothStep(const float& t)
{
	// Hermite Interpolation
	return t * t * (3 - 2 * t);

}

inline float smoothstepDeriv(const float& t)
{
	return t * (6 - 6 * t);
}

inline float quintic(const float& t) { return t * t * t * (t * (t * 6 - 15) + 10); }
inline float quinticDeriv(const float& t) { return 30 * t * t * (t * (t - 2) + 1); }

float consineRemap(const float& a, const float& b, const float& t)
{
	assert(t >= 0 && t <= 1);
	float tRemapCosine = (1 - std::cosf(t * mPI)) * 0.5f;
	return lerp(a, b, tRemapCosine);
}
float smoothstepRemap(const float& a, const float& b, const float& t)
{
	// float tRemapSmoothstep = t * t * (3 - 2 * t);

	// Ken Perlin ver.
	float t3 = std::powf(t, 3);
	float tRemapSmoothstep = 6 * t3 * t * t - 15.f * t3 * t + 10 * t3;
	return lerp(a, b, tRemapSmoothstep);
}

#endif