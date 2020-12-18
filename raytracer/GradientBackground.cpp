#include "GradientBackground.h"
#include "Ray.h"

Vec3f GradientBackground::get_color(const Vec3f& dir) const {
	const float f = (dir.y + 1) * 0.5;
	return bottom_color * f + top_color * (1 - f);
}