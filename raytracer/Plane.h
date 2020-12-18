#pragma once

#include "Shape.h"
#include "Vector.h"


class Plane : public Shape {
public:
	Vec3f origin;
	Vec3f normal;

	Plane(const Vec3f& origin, const Vec3f& normal)
		: origin(origin), normal(normal)
	{}

	virtual float intersect(const Ray& ray) const override;
	virtual Vec3f get_normal(const Vec3f& p) const override;
};