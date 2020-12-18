#include "Renderer.h"
#include "Ray.h"
#include "Scene.h"



Vec3f Renderer::cast_ray(const Ray& ray) const {
	m_depth++;
	if(m_depth > m_depth_limit)
		return m_current_scene->get_background_color(ray.direction);


	const auto intersection = m_current_scene->intersect(ray);

	if (intersection.shape) {
		return intersection.material->get_color(
			Material::surface_data(
				intersection.shape,
				intersection.material,
				&ray,
				intersection.t),
			*this);
	}

	return m_current_scene->get_background_color(ray.direction);
}