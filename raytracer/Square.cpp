#include "Square.h"
#include "Ray.h"
#include <algorithm>


Vec3f Square::get_normal(const Vec3f& v) const {
	return normal;
}

float Square::intersect(const Ray& ray) const {
	
	float denom = normal.dot(ray.direction);
	if (abs(denom) > 0.0001f)
	{
		float t = (origin - ray.origin).dot(normal) / denom;

		if (t < 0) return 0;

		const Vec3f P = ray.GetPosByT(t);

		//const Vec3f tangent(0.0, -normal.z, (1 - std::abs(normal.z)) * (normal.y > 0 ? 1 : -1));
		//const Vec3f tangent = Vec3f::normalize({ 0, -1, -1 });
		const Vec3f tangent = Vec3f::normalize(Vec3f(-1, 0, 0).cross(normal.y != 0 && normal.z != 0 ? normal : Vec3f(0, 1, 0)));
		const Vec3f V = Vec3f::normalize(P - origin);
		const float angle = std::acosf(V.dot(tangent));// +(V.x > 0 ? 3.14159265359 : 0);

		const float hs = width * 0.5;
		
		const float sec = hs * (1 / std::cosf(angle));
		const float csc = hs * (1 / std::sinf(angle));
		const float r = std::min(std::abs(sec), std::abs(csc));

		if ((P - origin).lengthSQ() < r*r) return t;
	}
	

	/*
	float denom = normal.dot(ray.direction);
	if (abs(denom) > 0.0001f)
	{
		float t = (origin - ray.origin).dot(normal) / denom;

		const Vec3f P = ray.GetPosByT(t);
		const Vec3f V = P - origin;

		const Vec3f tangent = Vec3f::normalize(Vec3f(-1, 0, 0).cross(normal.y != 0 && normal.z != 0 ? normal : Vec3f(0,1,0)));


		const float r = std::min(std::abs(sec), std::abs(csc));

		if (t >= 0 && (P - origin).lengthSQ() < r*r) return t;
	}
	*/

	return 0;
}