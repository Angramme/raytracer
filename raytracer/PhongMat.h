#pragma once

#include "Material.h"

class PhongMat : public Material {
public:
	Vec3f diffuse_color;
	Vec3f specular_color;
	float shininess;
	float metalness;

	PhongMat(const Vec3f& diffuse, const Vec3f& specular, const float& shininess, const float& metalness)
		: diffuse_color(diffuse), specular_color(specular), shininess(shininess), metalness(metalness)
	{}

	PhongMat(const Vec3f& diffuse, const float& shininess, const float& metalness)
		: diffuse_color(diffuse), specular_color(diffuse), shininess(shininess), metalness(metalness)
	{}

	virtual Vec3f get_color(const surface_data& data, const Renderer& renderer) const override;
};