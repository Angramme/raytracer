#pragma once

#include "Vector.h"
class Ray;

class Background {
public:
	virtual Vec3f get_color(const Vec3f& dir) const = 0;
};