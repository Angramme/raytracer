#pragma once

#include "Vector.h"
class Renderer;
class Ray;

class Shape;

class Material {
public:
	struct surface_data {
		const Shape* shape;
		const Material* material;
		const Ray* incident;
		const float t;

		surface_data(const Shape* shape, const Material* mat, const Ray* in, const float& t)
			: shape(shape), material(mat), incident(in), t(t)
		{}
	};

	virtual Vec3f get_color(const surface_data& data, const Renderer& renderer) const = 0;
};