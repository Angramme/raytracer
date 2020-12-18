#include "Plane.h"
#include "Ray.h"


Vec3f Plane::get_normal(const Vec3f& v) const {
	return normal;
}

float Plane::intersect(const Ray& ray) const {
	float denom = normal.dot(ray.direction);
	if (abs(denom) > 0.0001f)
	{
		float t = (origin - ray.origin).dot(normal) / denom;
		if (t >= 0) return t;
	}
	return 0;
}