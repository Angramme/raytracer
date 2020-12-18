#pragma once

#include "Vector.h"

class Ray {
public:
	Vec3f origin, direction;

	Ray(const Vec3f& origin, const Vec3f& dir)
		: origin(origin), direction(dir)
	{}
	
	Vec3f GetPosByT(const float& t) const;
};