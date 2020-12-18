#pragma once

#include "Shape.h"
#include "Vector.h"


class Disc : public Shape {
public:
	Vec3f origin;
	Vec3f normal;
	float r;

	Disc(const Vec3f& origin, const Vec3f& normal, const float& r)
		: origin(origin), normal(normal), r(r)
	{}

	virtual float intersect(const Ray& ray) const override;
	virtual Vec3f get_normal(const Vec3f& p) const override;
};
