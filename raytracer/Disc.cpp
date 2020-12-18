#include "Disc.h"
#include "Ray.h"


Vec3f Disc::get_normal(const Vec3f& v) const {
	return normal;
}

float Disc::intersect(const Ray& ray) const {
	float denom = normal.dot(ray.direction);
	if (abs(denom) > 0.0001f)
	{
		float t = (origin - ray.origin).dot(normal) / denom;
		if (t >= 0 && (ray.GetPosByT(t) - origin).lengthSQ() < r*r ) return t;
	}
	return 0;
}