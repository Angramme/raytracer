#pragma once

#include "Shape.h"
#include "Vector.h"


class Square : public Shape {
public:
	Vec3f origin;
	Vec3f normal;
	float width;
	float height;

	Square(const Vec3f& origin, const Vec3f& normal, const float& size)
		: origin(origin), normal(normal), width(size), height(size)
	{}

	Square(const Vec3f& origin, const Vec3f& normal, const float& width, const float& height)
		: origin(origin), normal(normal), width(width), height(height)
	{}

	virtual float intersect(const Ray& ray) const override;
	virtual Vec3f get_normal(const Vec3f& p) const override;
};
