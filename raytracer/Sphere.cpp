#include "Sphere.h"
#include "Ray.h"

float Sphere::intersect(const Ray& ray) const {
	const Vec3f& o = ray.origin;
	const Vec3f& d = ray.direction;

	const Vec3f v = o - center;

	const float b = 2 * v.dot(d);
	const float c = v.dot(v) - radius*radius;
	float delta = b * b - 4 * c;

	//if (delta < 1e-4) //slightly faster than delta <= 0 and gives same results :)
	if(delta <= 0)
		return 0; //no intersection

	const float sqrtdelta = sqrt(delta);
	const float t1 = (-b - sqrtdelta) / 2;
	const float t2 = (-b + sqrtdelta) / 2;

	const float t = (t1 < t2) ? t1 : t2; // get the first intersection only

	if (t < 0) {
		const float bigt = (t1 < t2) ? t2 : t1;
		return bigt < 0 ? 0 : bigt;
	}
	
	return t;
}


Vec3f Sphere::get_normal(const Vec3f& p) const {
	return (p - center) * (1.0f/radius);
}