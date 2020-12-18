#include "PhongMat.h"

#include "Renderer.h"
#include "Ray.h"
#include "Shape.h"
#include "Scene.h"

#include <cmath>
#include <algorithm>



Vec3f PhongMat::get_color(const surface_data& data, const Renderer& renderer) const {
	const Vec3f P = data.incident->GetPosByT(data.t);
	const Vec3f N = data.shape->get_normal(P);
	const Scene& scene = *renderer.get_scene();

	Vec3f Sum_Vec(0, 0, 0);

	for (const std::unique_ptr<Light>& light : scene.get_lights()) {
		Vec3f L = light->position - P; //direction
		float distanceSQ = L.lengthSQ();
		L.normalize();

		bool occluded = true;
		{
			const auto occlusion = scene.intersect(Ray(P + N * 0.01 /* buggy if directly on the surface */, L));
			const float& t = occlusion.t;
			occluded = t != 0 && t*t < distanceSQ;
		}

		Vec3f diffuse(0, 0, 0);
		Vec3f specular(0, 0, 0);

		if (!occluded) {
			Vec3f intensity = light->component_intensity * light->intensity;

			//light falloff following inverse square-root formula
			intensity *= 1 / distanceSQ;


			diffuse = intensity * std::max(N.dot(L), 0.0f) * (1 / 3.14159265359f);
			//                                                         energy conservation __________/\ 

			const Vec3f R = Vec3f::reflect(-L, N);
			const Vec3f V = -data.incident->direction;

			const float& n = shininess;
			float spec = std::powf(std::max(V.dot(R), 0.0f), n);
			specular = light->component_intensity * ((n + 2) / (2 * 3.14159265359f)) * spec;
			//                                                       energy conservation __________/\ 
		}

		//sum it up
		float ks = metalness;
		float kd = 1 - ks;
		// kd + ks == 1  cuz energy conservation

		Sum_Vec += diffuse_color * diffuse * kd + specular_color * specular * ks;
	}

	const Vec3f background = diffuse_color * scene.get_background_color(N) * (1 - metalness);
	return Sum_Vec + background;
}