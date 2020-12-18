#pragma once

#include "Vector.h"

class Light {
public:
	Vec3f position;
	Vec3f component_intensity; // 0-1
	float intensity;

	Light(const Vec3f& pos, const Vec3f& color)
		: position(pos), component_intensity(color), intensity(1)
	{}

	Light(const Vec3f& pos, const Vec3f& color_norm, const float& intensity)
		: position(pos), component_intensity(color_norm), intensity(intensity)
	{}
};