#pragma once

#include "Background.h"
#include "Vector.h"

class GradientBackground : public Background {
public:
	Vec3f top_color;
	Vec3f bottom_color;

	GradientBackground(const Vec3f& top_c, const Vec3f& bottom_c)
		: top_color(top_c), bottom_color(bottom_c)
	{}

	virtual Vec3f get_color(const Vec3f& dir) const override;
};