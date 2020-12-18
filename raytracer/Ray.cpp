#include "Ray.h"

Vec3f Ray::GetPosByT(const float& t) const {
	return origin + direction * t;
}