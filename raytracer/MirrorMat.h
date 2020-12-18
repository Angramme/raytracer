#pragma once

#include "Material.h"
#include "Vector.h"

class MirrorMat : public Material {
public:
	Vec3f color;
	
	MirrorMat()
		: color(0.9,0.9,0.9)
	{}

	MirrorMat(const Vec3f& color)
		: color(color)
	{}

	virtual Vec3f get_color(const surface_data& data, const Renderer& renderer) const override;
};