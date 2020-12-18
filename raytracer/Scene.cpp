#include <limits>
#include <cmath>
#include "Scene.h"
#include "Shape.h"
#include "Vector.h"
#include "Light.h"
#include "Ray.h"

Scene::intersection_data Scene::intersect(const Ray& ray) const {
	float min_t = std::numeric_limits<float>::max();
	Shape* close_shape_ptr = nullptr;
	size_t close_material_index = 0;

	for (const std::unique_ptr<Shape>& shape_ptr : m_shape_ptrs) {
		float t = shape_ptr->intersect(ray);
		if (t == 0) { //t = 0 -> no intersection found
			continue;
		}
		else if (t < min_t) { //is it closer ?
			min_t = t;
			close_shape_ptr = shape_ptr.get();
			close_material_index = &shape_ptr - &m_shape_ptrs[0]; //get the index
		}
	}

	return { close_shape_ptr, m_material_ptrs[close_material_index].get(), close_shape_ptr != nullptr ? min_t : 0 /* t = 0 -> no intersection */ };
}



void Scene::push(const std::unique_ptr<Shape>& shape, const std::unique_ptr<Material>& material) {
	m_shape_ptrs.push_back(std::move(const_cast<std::unique_ptr<Shape>&>(shape)));
	m_material_ptrs.push_back(std::move(const_cast<std::unique_ptr<Material>&>(material)));
}
void Scene::push(const std::unique_ptr<Light>& light) {
	m_light_ptrs.push_back(std::move(const_cast<std::unique_ptr<Light>&>(light)));
}

