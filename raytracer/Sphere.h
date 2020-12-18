#pragma once

#include "Shape.h"
#include "Vector.h"
class Ray;

class Sphere : public Shape {
public:
	Vec3f center;
	float radius;

	Sphere(Vec3f c, float r)
		: center(c), radius(r)
	{}

	virtual float intersect(const Ray& ray) const override;
	virtual Vec3f get_normal(const Vec3f& p) const override;
};