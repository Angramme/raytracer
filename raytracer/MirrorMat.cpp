#include "MirrorMat.h"

#include "Ray.h"
#include "Vector.h"
#include "Shape.h"
#include "Scene.h"
#include "Renderer.h"



Vec3f MirrorMat::get_color(const surface_data& data, const Renderer& renderer) const {
	const Vec3f P = data.incident->GetPosByT(data.t);
	const Vec3f N = data.shape->get_normal(P);

	const Vec3f R = Vec3f::reflect(data.incident->direction, N);

	const Ray newray(P + N * 0.01, R);

	return renderer.cast_ray(newray) * color;
}